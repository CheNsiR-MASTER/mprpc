/*
 * @Author: your name
 * @Date: 2022-04-27 20:49:53
 * @LastEditTime: 2022-04-29 22:28:41
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/example/callee/userService.cc
 */
#include <iostream>
#include <string>
#include "user.pb.h"
#include "rpcprovider.h"
#include "mprpcapplication.h"
#include "mprpccontroller.h"

// UserService 原来是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
class UserService : public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd) // 使用在Rpc服务发布端 （rpc 服务调用者）
    {
        std::cout << "callee : Login" << std::endl;
        std::cout << "name :" << name << " pwd:" << pwd << std::endl;
        return true;
    }

    bool Register(int id, std::string name, std::string pwd)
    {
        std::cout << "callee : Register" << std::endl;
        std::cout <<"id : " << id << "name :" << name << " pwd:" << pwd << std::endl;
        return true;
    }
    /*
        重写了基类UserServiceRpc的虚函数，一下这些方法都是框架直接调用的
        流程
        caller  =>  Login(LoginRequest)  => muduo  => callee
        callee  =>  Login(LoginRequest)  => void Login(...)
    */ 
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数,应用获取相应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();
        // 做本地业务
        bool login_result = Login(name,pwd);
        // 把响应写入，包括错误码，错误消息，执行结果

        fixbug::ResultCode *result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(login_result);
        // 执行回调函数 ==> 完成 响应消息的 序列化和网络发送(都是由框架完成)
        done->Run();
    }

    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数,应用获取相应数据做本地业务
        int id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();
        // 做本地业务
        bool register_result = Register(id,name,pwd);
        // 把响应写入，包括错误码，错误消息，执行结果

        fixbug::ResultCode *result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(register_result);
        // 执行回调函数 ==> 完成 响应消息的 序列化和网络发送(都是由框架完成)
        done->Run();
    }
    
};

int main(int argc, char** argv)
{
    // 调用框架的初始化
    MprpcApplication::Init(argc,argv); 
    // 创建一个rpc网络服务对象，发布 UserService 到 rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());
    // 启动一个RPC节点 ， Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();
    return 0;
}