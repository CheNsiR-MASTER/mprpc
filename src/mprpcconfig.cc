/*
 * @Author: your name
 * @Date: 2022-04-28 00:12:52
 * @LastEditTime: 2022-04-28 11:03:26
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/mprpcconfig.cc
 */
#include "mprpcconfig.h"

std::string MprpcConfig::Load(std::string key)
{
    if(m_configMap.count(key))
    {
        return m_configMap[key];
    }
    return "";
}

void MprpcConfig::trim(std::string& str)
{
    // 1. 处理前导空格 和 后导空格
    int idx = str.find_first_not_of(' ');
    if(idx != -1)
    {
        str = str.substr(idx,str.size() - idx);
    }
    idx = str.find_last_not_of(' ');
    if(idx != -1)
    {
        str = str.substr(0,idx + 1);
    }
}

// 读取的配置文件只有几种情况
// 1. 注释 #      2. 开头带有空格     3. 遇到 = 前面为key 后面为 value     4. 没有 =    
void MprpcConfig::LoadConfigFile(const char* config_file)
{
    FILE* fp = fopen(config_file,"r");
    if(fp == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    while(!feof(fp))
    {
        char buf[512] = {0};
        fgets(buf,512,fp);
        std::string str(buf);

        trim(str);
        // 2.处理注释 和 空白行
        if(str[0] == '#' || str.size() == 0)
        {
            continue;
        }
        // 处理找不到 = 的情况
        int idx = str.find('=');
        if(idx == -1) continue;
        
        // 找到了符合要求的行
        std::string key = str.substr(0,idx);
        trim(key);
        std::string value = str.substr(idx + 1,str.size() - idx);
        int endidx = str.find('\n');
        value = str.substr(idx + 1,endidx - idx - 1);
        trim(value);
        m_configMap.insert({key,value});
    }

}