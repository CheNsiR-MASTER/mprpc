#pragma once
#include <unordered_map>
#include <string>

// 框架读取配置文件类
// rpcserver_ip   rpcserver_port zookeeperip   zookeeperport
class MprpcConfig
{
public:
    std::string Load(std::string key);
    void LoadConfigFile(const char* config_file);
    void trim(std::string& str);
private:
    std::unordered_map<std::string,std::string> m_configMap;
};