/*
 * @Author: your name
 * @Date: 2022-04-29 19:36:43
 * @LastEditTime: 2022-04-29 22:21:35
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/include/mprpccontrol.h
 */
#pragma once
#include <iostream>
#include <string>
#include <google/protobuf/service.h>

class MprpcController:public google::protobuf::RpcController {
 public:
    MprpcController();
    void Reset();

    bool Failed();

    std::string ErrorText();

    void SetFailed(const std::string& reason);
// 以下成员函数未实现
    void StartCancel();
    bool IsCanceled();
    void NotifyOnCancel(google::protobuf::Closure* callback);
private:
    std::string m_errormsg;
    bool m_flag;
};
