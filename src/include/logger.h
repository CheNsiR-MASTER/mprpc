/*
 * @Author: your name
 * @Date: 2022-04-29 20:12:48
 * @LastEditTime: 2022-04-29 22:40:55
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/include/logger.h
 */
#pragma once
#include "lockqueue.h"
#include <thread>
#include <string>
#include <iostream>

// 定义宏 LOG_INFO("XXX %d %s", 20, "xxxx")
#define LOG_INFO(format, ...) \
    do \
    { \
        Logger &logger = Logger::GetLogger(); \
        logger.SetLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, format, ##__VA_ARGS__); \
        logger.log(c); \
    } while(0) \

#define LOG_ERROR(format,...) \
    do \
    { \
        Logger &logger = Logger::GetLogger(); \
        logger.SetLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c,1024,format, ##__VA_ARGS__); \
        logger.log(c); \
    } while(0) \
// 定义日志级别
enum Level
{
    INFO,
    ERROR,
};

class Logger
{
public:
    static Logger& GetLogger();
    
    // 设定日志级别
    void SetLevel(Level level);
    // 写日志
    void log(std::string text);
private:
    int m_loglevel; 
    Logger();
    Lockqueue<std::string> logger_queue;
    Logger(const Logger& logger) = delete;
    Logger(Logger&&) = delete;
};
