/*
 * @Author: your name
 * @Date: 2022-05-02 13:18:34
 * @LastEditTime: 2022-05-02 13:45:05
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/example/testZk/testGetNode.cc
 */
#include "zookeeperutil.h"
#include <iostream>
int main()
{
    ZkClient zkcli;
    zkcli.Start();
    std::string host_data = zkcli.GetData("/RpcService/GetFriendsList");
    std::cout << host_data << std::endl;
}
