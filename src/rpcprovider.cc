/*
 * @Author: your name
 * @Date: 2022-04-27 21:58:59
 * @LastEditTime: 2022-05-02 14:15:48
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/rpcprovider.cc
 */
#include "rpcprovider.h"
// 框架提供给外部使用的，可以发布rpc方法的函数接口
void RpcProvider::NotifyService(google::protobuf::Service* service)
{
    // 获取描述对象的信息的指针
    const google::protobuf::ServiceDescriptor* servicedesc = service->GetDescriptor();
    ServiceInfo serviceinfo;

    // 获取服务的名称
    std::string serviceName = servicedesc->name();
    // 获取服务的数量
    int methodCnt = servicedesc->method_count();

    // 将所有服务插入 serviceInfo  => 再将所有 serviceInfo 插入 => serviceInfoMap
    for(int i = 0; i < methodCnt; ++i)
    {
        const google::protobuf::MethodDescriptor* pmethodDesc = servicedesc->method(i);
        std::string methodName = pmethodDesc->name();
        serviceinfo.m_methodMap.insert({methodName,pmethodDesc});
        
        LOG_INFO("method name : %s => %s:%s:%d",methodName.c_str(),__FILE__,__FUNCTION__,__LINE__);
    }
    serviceinfo.m_service = service;
    m_serviceInfoMap.insert({serviceName,serviceinfo});

}


void RpcProvider::Run()
{
    // 获取配置文件中的端口号 和 ip地址
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip,port);

    // 创建 tcpServer 对象
    muduo::net::TcpServer server(&m_eventLoop,address,"RpcServer");
    // 绑定连接回调和消息读写回调的方法
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this,
                                std::placeholders::_1));

    server.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,
                                std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

    // 设置muduo库的线程数量
    server.setThreadNum(4);

    
    // 把当前rpc节点上要发布的服务全部注册到zk上面，让rpc client可以从zk上发现服务
    // session timeout   30s     zkclient 网络I/O线程  1/3 * timeout 时间发送ping消息
    ZkClient zkCli;
    zkCli.Start();
    // service_name为永久性节点    method_name为临时性节点
    for (auto &sp : m_serviceInfoMap) 
    {
        // /service_name   /UserServiceRpc
        std::string service_path = "/" + sp.first;
        zkCli.Create(service_path.c_str(), nullptr, 0);
        for (auto &mp : sp.second.m_methodMap)
        {
            // /service_name/method_name   /UserServiceRpc/Login 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data, "%s:%d", ip.c_str(), port);
            // ZOO_EPHEMERAL表示znode是一个临时性节点
            zkCli.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);
        }
    }

    // 启动
    server.start();

    // 进入事件监听循环
    m_eventLoop.loop();
}

void RpcProvider::OnConnection (const muduo::net::TcpConnectionPtr& conn)
{
    if(!conn->connected())
    {
        conn->shutdown();
    }
}

/* 
    在框架内部，RpcProvider 和 RpcConsumer 协商好之间通信用的protobuf数据类型
    包括 service_name  method_name  args
    如何识别 service_name 和 method_name   需要定义 protobuf 的 message 类型，进行序列化和反序列化
    
    将数据的前四个字节，定义为 int类型   -->  表示 数据头的长度 
                                      -->  service_name + method_name + args_size
    总的字节流  ： header_size（4bytes） + header_str + args_str
*/ 
// 已经建立连接用户的读写事件回调
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp timestamp)
{
    // 从网络上接受一个字节流 Login args
    std::string recv_buf = buffer->retrieveAllAsString(); // 将所有字节流都转化为string

    // 从字节流接受前四个字符
    int header_size = 0;
    recv_buf.copy((char *)&header_size,4,0);
    
    // 根据header_size读取数据投的原始字符流，反序列化数据，得到rpc请求的详细信息
    std::string rpc_header_str = recv_buf.substr(4,header_size);
    mprpc::rpcHeader rpchead;
    std::string service_name;
    std::string method_name ;
    int args_size;
    std::cout << rpc_header_str << std::endl;
    if(rpchead.ParseFromString(rpc_header_str))
    {
        // 数据反序列化成功
        service_name = rpchead.service_name();
        method_name = rpchead.method_name();
        args_size = rpchead.args_size();
    }
    else
    {
        // 数据反序列化失败
        LOG_ERROR("rpc_header_str : %s => %s:%s:%d",rpc_header_str.c_str(),__FILE__,__FUNCTION__,__LINE__);
        return;
    }
    std::string args_str = recv_buf.substr(header_size + 4, args_size);

    // 调试信息
    std::cout << "-------------------------------" << std::endl;
    std::cout << "service_name : " << service_name << std::endl;
    std::cout << "method_name : " << method_name << std::endl;
    std::cout << "args_str : " << args_str << std::endl;
    std::cout << "-------------------------------" << std::endl;

    // 获取 service 对象 和 method 对象
    ServiceInfo serviceinfo;

    if (!m_serviceInfoMap.count(service_name))
    {
        LOG_ERROR("%s is not exist!  => %s:%s:%d ",service_name.c_str(),__FILE__,__FUNCTION__,__LINE__);
        return;
    }

    serviceinfo = m_serviceInfoMap[service_name];
   
    if (!serviceinfo.m_methodMap.count(method_name))
    {
        std::cout << service_name << ":" << method_name << " is not exist!" << std::endl;
        return;
    }

    google::protobuf::Service *service = m_serviceInfoMap[service_name].m_service; // 获取service对象  new UserService
    const google::protobuf::MethodDescriptor *method =serviceinfo.m_methodMap[method_name]; // 获取method对象  Login
    // google::protobuf::Service* service = serviceinfo.m_service;

    // const google::protobuf::MethodDescriptor* method;

    // 生成 request 请求参数 和 response 响应参数
    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str))
    {
        // 没有正确的反序列化出 参数字符串
        return;
    }
    // request 已经反序列化完成
    google::protobuf::Message* response = service->GetResponsePrototype(method).New();


    // 通过rpc节点远程调用
    // 给下面的method 方法的调用 绑定一个 Closure的调用

    google::protobuf::Closure* done = google::protobuf::NewCallback
                        <RpcProvider,const muduo::net::TcpConnectionPtr&,google::protobuf::Message*>
                        (this,&RpcProvider::SendRpcResponse,conn,response);
    service->CallMethod(method,nullptr,request,response, done);
}

void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn,
                                            google::protobuf::Message* response)
{
    std::string response_str;
    if(response->SerializeToString(&response_str))
    {
        conn->send(response_str);
    }
    conn->shutdown(); // 关闭连接
}