/*
 * @Author: your name
 * @Date: 2022-04-28 21:10:54
 * @LastEditTime: 2022-05-02 14:15:36
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/include/mprpcchannel.h
 */
#pragma once
#include "mprpcapplication.h"
#include "google/protobuf/service.h"
#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"
#include "provider.pb.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "zookeeperutil.h"
class RpcChannel : public google::protobuf::RpcChannel
{
public:
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller,
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
                          google::protobuf::Closure* done);
};