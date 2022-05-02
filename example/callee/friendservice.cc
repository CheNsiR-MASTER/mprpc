/*
 * @Author: your name
 * @Date: 2022-04-29 16:36:04
 * @LastEditTime: 2022-05-02 14:24:23
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/example/callee/friendservice.cc
 */
#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "mprpcchannel.h"
#include <vector>
#include "mprpccontroller.h"
#include "logger.h"

class FriendService: public fixbug::FriendServiceRpc
{
public:
// 模拟业务
    std::vector<std::string> GetFriendList(int userid)
    {
        std::cout << "do GetFriendsList service! userid:" << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("chensir");
        vec.push_back("chensir Master");
        vec.push_back("chensir chensir");
        return vec;
    }
    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendsListRequest* request,
                       ::fixbug::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done)
    {
        int32_t userid = request->userid();
        auto vec = GetFriendList(userid);

        fixbug::ResultCode* result =  response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");

        for(auto& x : vec)
        {
            std::string* p = response->add_friends();
            *p = x;
        }
        done->Run();
    }
};


int main(int argc, char** argv)
{
    // 调用框架的初始化
    MprpcApplication::Init(argc,argv); 
    // 创建一个rpc网络服务对象，发布 UserService 到 rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    // 启动一个RPC节点 ， Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();
    return 0;
}