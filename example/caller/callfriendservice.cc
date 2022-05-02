/*
 * @Author: your name
 * @Date: 2022-04-29 16:58:45
 * @LastEditTime: 2022-05-02 14:25:36
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/example/caller/callfriendservice.cc
 */
#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

int main(int argc, char** argv)
{
       // 初始化一次 app
    MprpcApplication::Init(argc, argv);

    // 需要调用
    fixbug::FriendServiceRpc_Stub stub(new RpcChannel());

    fixbug::GetFriendsListRequest request;
    fixbug::GetFriendsListResponse response;

    request.set_userid(2000);
    stub.GetFriendsList(nullptr,&request,&response,nullptr);
    int size = response.friends_size();

    for(int i = 0; i < size; ++i)
    {
        std::cout << response.friends(i) << std::endl; 
    }
    return 0;
}