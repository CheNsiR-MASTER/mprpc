/*
 * @Author: your name
 * @Date: 2022-05-02 12:45:20
 * @LastEditTime: 2022-05-02 14:16:43
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/zookeeperutil.cc
 */
#include "zookeeperutil.h"
#include <iostream>
void global_watcher(zhandle_t *zh, int type, 
        int state, const char *path,void *watcherCtx)
{
    if(type == ZOO_SESSION_EVENT)
    {
        if(state == ZOO_CONNECTED_STATE)
        {
            sem_t* sem = (sem_t*) zoo_get_context(zh);
            sem_post(sem);
        }
    }
}

ZkClient::ZkClient() : m_zhandle(nullptr) {}
ZkClient::~ZkClient()
{
    if(m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle);
    }
}
// 连接zkserver
void ZkClient::Start()
{
    // 从配置文件读取 zkserver的ip 和 端口号
    std::string host = MprpcApplication::GetInstance().GetConfig().Load("zookeeperip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("zookeeperport");
    
    // 需要组合成 zk规定的格式 ip:port
    std::string connstr = host + ":" + port;

    // zookeeper_mt  -> 多线程版本  zookeeper_st  -> 单线程版本
    // 多线程版本包含了三次线程创建
    m_zhandle = zookeeper_init(connstr.c_str(),global_watcher,30000,nullptr,nullptr,0);
    if(nullptr == m_zhandle)
    {
        std::cout << "------- zookeeper init error --------" << std::endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);

    zoo_set_context(m_zhandle,&sem);
    sem_wait(&sem);

    std::cout << "zookeeper_init success!" << std::endl;
    
}
void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buffer[128];
    int buffer_len = sizeof path_buffer;
    int flag;
    // 判断 节点是否存在，如果存在，就不需要创建节点
    flag = zoo_exists(m_zhandle,path,0,nullptr);
    if(ZNONODE == flag)
    {
        // 创建指定的 node节点
        flag = zoo_create(m_zhandle,path,data,datalen,
                    &ZOO_OPEN_ACL_UNSAFE,state,path_buffer,buffer_len);
        if(flag == ZOK)
        {
            std::cout << "znode create success... path:" << path << std::endl;
        }
        else
        {
            std::cout << "flag:" << flag << std::endl;
			std::cout << "znode create error... path:" << path << std::endl;
			exit(EXIT_FAILURE);
        }
    }
}

// 根据指定的 path 获取相应 node节点的值
std::string ZkClient::GetData(const char* path)
{
    char buffer[128];
    int buffer_len = sizeof buffer;
    int flag = zoo_get(m_zhandle, path, 0, buffer, &buffer_len,nullptr);
    if(flag != ZOK)
    {
        std::cout << "get znode error... path:" << path << std::endl;
		return "";
    }
    else
    {
        return buffer;
    }
}