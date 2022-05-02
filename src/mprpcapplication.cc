/*
 * @Author: your name
 * @Date: 2022-04-27 21:37:29
 * @LastEditTime: 2022-04-28 11:57:21
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/mprpcapplication.cc
 */
#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>

void showHelper()
{
    std::cout << "command -i <configure file> " << std::endl;
}

MprpcConfig MprpcApplication::m_config;

void MprpcApplication::Init(int argc, char** argv)
{
    if(argc < 2)
    {
        showHelper();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;

    while((c = getopt(argc,argv,"i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            showHelper();
            exit(EXIT_FAILURE);
        case ':':
            showHelper();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
    // 开始加载文件
    m_config.LoadConfigFile(config_file.c_str());

    // 测试
    // std::cout << "rpcserverip"<< m_config.Load("rpcserverip") << std::endl;
    // std::cout << "rpcserverport"<< m_config.Load("rpcserverport") << std::endl;
    // std::cout << "zookeeperip"<< m_config.Load("zookeeperip") << std::endl;
    // std::cout << "zookeeperport"<< m_config.Load("zookeeperport") << std::endl;
}

MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig&  MprpcApplication::GetConfig()
{
    return m_config;
}