/*
 * @Author: your name
 * @Date: 2022-04-28 21:13:10
 * @LastEditTime: 2022-05-02 14:18:13
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/mprpcchannel.cc
 */
#include "mprpcchannel.h"

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                        google::protobuf::RpcController* controller,
                        const google::protobuf::Message* request,
                        google::protobuf::Message* response,
                        google::protobuf::Closure* done)
{
    const google::protobuf::ServiceDescriptor* sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();

    // 获取参数 序列化长度
    uint32_t args_size = 0;
    std::string args_str;

    //序列化
    if(request->SerializeToString(&args_str))
    {
        args_size = args_str.size(); 
    }
    else
    {
        controller->SetFailed( "serialize request error");
        return;
    }

    // 定义 rpc请求的header
    mprpc::rpcHeader rpcheader;
    rpcheader.set_service_name(service_name);
    rpcheader.set_method_name(method_name);
    rpcheader.set_args_size(args_size);
    
    uint32_t header_size = 0;
    std::string rpc_header_str;
    if(rpcheader.SerializeToString(&rpc_header_str))
    {
        header_size = rpc_header_str.size();
    }
    else 
    {
        controller->SetFailed( "serialize request error");
        return;
    }
    // 组合待发送的字符串
    std::string send_rpc_str;
    send_rpc_str.insert(0, std::string((char*)&header_size, 4)); // header_size
    send_rpc_str += rpc_header_str; // rpcheader
    send_rpc_str += args_str; // args

    std::cout << send_rpc_str << std::endl;
    
    // 调试信息
    std::cout << "-------------------------------" << std::endl;
    std::cout << "service_name : " << service_name << std::endl;
    std::cout << "method_name : " << method_name << std::endl;
    std::cout << "args_str : " << args_str << std::endl;
    std::cout << "-------------------------------" << std::endl;

    // 使用tcp编程，实现rpc方法的远程调用
    // 1. 创建socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    //assert(clientfd != -1);
    // 通过单例 拿到配置文件中的 ip地址 和 端口号
    // std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    // int port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    ZkClient zkCli;
    zkCli.Start();
    //  /UserServiceRpc/Login
    std::string method_path = "/" + service_name + "/" + method_name;
    // 127.0.0.1:8000
    std::string host_data = zkCli.GetData(method_path.c_str());
    if (host_data == "")
    {
        controller->SetFailed(method_path + " is not exist!");
        return;
    }
    int idx = host_data.find(":");
    if (idx == -1)
    {
        controller->SetFailed(method_path + " address is invalid!");
        return;
    }
    std::string ip = host_data.substr(0, idx);
    uint16_t port = atoi(host_data.substr(idx+1, host_data.size()-idx).c_str()); 

    std::cout << ip << " " << port << std::endl;
    struct sockaddr_in addr;
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    
    // 发起连接
    if(-1 == connect(clientfd,(struct sockaddr*)& addr,sizeof addr))
    {
        close(clientfd);
        controller->SetFailed( "connection error");
        exit(EXIT_FAILURE);
    }
    
    if(-1 == send(clientfd,send_rpc_str.c_str(),send_rpc_str.size(),0))
    {
        close(clientfd);
        controller->SetFailed( "send rpc message error");
        return;
    }
    
    // 接受buffer
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1 == (recv_size = recv(clientfd,recv_buf,1024,0)))
    {
        controller->SetFailed( "recv buffer error");
        close(clientfd);
        return;
    }
    
    // 反序列化
    //std::string response_str(recv_buf,0,recv_size);
    if(!response->ParseFromArray(recv_buf, recv_size))
    {
        controller->SetFailed( "serialize request error");
        close(clientfd);
        return;
    }
    
    close(clientfd);
}