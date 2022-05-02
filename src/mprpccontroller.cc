/*
 * @Author: your name
 * @Date: 2022-04-29 19:45:28
 * @LastEditTime: 2022-04-29 19:50:00
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/mprpccontroller.cc
 */
#include "mprpccontroller.h"

MprpcController::MprpcController() :m_flag(false),m_errormsg("") { }
void MprpcController::Reset() 
{
    m_flag = false;
    m_errormsg = "";
};

bool MprpcController::Failed()
{
    return m_flag;
};

std::string MprpcController::ErrorText()
{
    return m_errormsg;
};

void MprpcController::SetFailed(const std::string& reason)
{
    m_flag = true;
    m_errormsg = reason;
};

// 以下成员函数未实现
void MprpcController::StartCancel() {};
bool MprpcController::IsCanceled(){};
void MprpcController::NotifyOnCancel(google::protobuf::Closure* callback){};