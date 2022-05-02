/*
 * @Author: your name
 * @Date: 2022-04-26 20:51:27
 * @LastEditTime: 2022-04-27 20:19:49
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/test/testProtobuf/main.cc
 */
#include "test.pb.h"
#include <iostream>
#include <string>

int main()
{
    // // 封装了login请求对象的数据
    // fixbug::LoginRequest req;
    // req.set_name("chensir");
    // req.set_pwd("990517");

    // // 将对象序列化
    // std::string send_buf;
    // if(req.SerializeToString(&send_buf))
    // {
    //     std::cout << send_buf << std::endl;
    // }

    // // 将对象反序列化
    // // 从send_str 反序列化一个login请求对象
    // fixbug::LoginRequest reqB;
    // if(reqB.ParseFromString(send_buf))
    // {
    //     std::cout << reqB.name() << std::endl;
    //     std::cout << reqB.pwd() << std::endl;
    // }

    fixbug::LoginResponse rsp;
    fixbug::resultCode* r1 = rsp.mutable_r1();
    r1->set_errorcode(1);
    r1->set_errormsg("error message : ....");

    fixbug::GetFriendListResponse gfr;
    fixbug::User* user1 = gfr.add_friend_list();
    user1->set_age(22);
    user1->set_name("chensir");
    user1->set_sex(fixbug::User::MAN);

    // 查看有多少链表
    int n = gfr.friend_list_size();
    std::cout << n << std::endl;
    // 可以通过下标访问
    fixbug::User u1 = gfr.friend_list(0); 
    std:: cout << u1.age() << " " << u1.name() << " " << u1.sex() << std::endl;
}
