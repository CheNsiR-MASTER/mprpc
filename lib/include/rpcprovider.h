/*
 * @Author: your name
 * @Date: 2022-04-27 21:45:50
 * @LastEditTime: 2022-05-02 14:15:25
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/include/rpcprovider.h
 */
#pragma once
#include "google/protobuf/service.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <google/protobuf/descriptor.h>
#include "mprpcapplication.h"
#include <functional>
#include <iostream>
#include "provider.pb.h"
#include "logger.h"
#include "zookeeperutil.h"

class RpcProvider
{
public:
    //RpcProvider();
    void NotifyService(google::protobuf::Service* service);
    void Run();
private:
    std::unique_ptr<muduo::net::TcpServer> m_tcoserverptr;
    // 组合了 eventLoop
    struct ServiceInfo
    {
        std::unordered_map<std::string,const google::protobuf::MethodDescriptor*> m_methodMap;
        google::protobuf::Service* m_service;
    };
    std::unordered_map<std::string,ServiceInfo> m_serviceInfoMap;
    muduo::net::EventLoop m_eventLoop;
    void OnConnection (const muduo::net::TcpConnectionPtr& conn);
    void OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp timestamp);
    // 绑定 Closure 回调操作， 用于序列化 Rpc的响应 和 网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr& ,google::protobuf::Message* response);

};