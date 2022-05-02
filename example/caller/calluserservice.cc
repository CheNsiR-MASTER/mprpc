/*
 * @Author: your name
 * @Date: 2022-04-28 19:42:14
 * @LastEditTime: 2022-04-29 22:29:13
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/example/caller/calluserservice.cc
 */
#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

int main(int argc, char** argv)
{
    // 初始化一次 app
    MprpcApplication::Init(argc, argv);

    // 需要调用
    fixbug::UserServiceRpc_Stub stub(new RpcChannel());
    fixbug::LoginRequest request;
    request.set_name("chensir");
    request.set_pwd("990517");
    fixbug::LoginResponse response;
        // 创建 controller
    MprpcController* controller;
    stub.Login(controller,&request,&response,nullptr);

    if(controller->Failed())
    {
        std::cout << "Login error : " << controller->ErrorText() << std::endl;
    }
    // Login调用成功，开始返回响应
    if(0 == response.result().errcode())
    {
        std::cout << "success : " << response.success() << std::endl;
    }
    else
    {
        std::cout << "error : " << response.result().errmsg() << std::endl;
    }

    fixbug::RegisterRequest requestReg;
    requestReg.set_id(2000);
    requestReg.set_name("chenyixing");
    requestReg.set_pwd("051799");
    fixbug::RegisterResponse responseReg;
    stub.Register(nullptr,&requestReg,&responseReg,nullptr);
    // 注册调用成功，开始返回响应
    if(0 == responseReg.result().errcode())
    {
        std::cout << "success : " << responseReg.success() << std::endl;
    }
    else
    {
        std::cout << "error : " << responseReg.result().errmsg() << std::endl;
    }

    return 0;
}