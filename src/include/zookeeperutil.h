/*
 * @Author: your name
 * @Date: 2022-05-02 12:33:17
 * @LastEditTime: 2022-05-02 12:45:40
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEude
 * @FilePath: /linux/RPC/src/include/zookeeperutil.h
 */
#pragma once
#include <zookeeper/zookeeper.h>
#include "mprpcapplication.h"
#include <semaphore.h>
#include <string>
class ZkClient
{
public:
    ZkClient();
    ~ZkClient();
    void Start();
    void Create(const char *path, const char *data, int datalen, int state=0);
    std::string GetData(const char* path);
private:
    // zk客户端句柄
    zhandle_t* m_zhandle;
};