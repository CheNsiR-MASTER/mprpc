/*
 * @Author: your name
 * @Date: 2022-05-02 13:08:44
 * @LastEditTime: 2022-05-02 14:08:40
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/example/testZk/test1.cc
 */
#include "zookeeperutil.h"
#include <iostream>

int main()
{
    ZkClient zkcli;
    zkcli.Start();
    std::string serverpath = '/' + "RpcService";
    zkcli.Create(serverpath.c_str(),nullptr,0);

    std::string methodpath = serverpath + '/' + "GetFriendsList";
    char methodval[128];
    sprintf(methodval,"%s:%d","127.0.0.1",8000);
    zkcli.Create(methodpath.c_str(),methodval,sizeof methodval,ZOO_EPHEMERAL);
    while(1){}
}