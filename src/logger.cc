/*
 * @Author: your name
 * @Date: 2022-04-29 22:01:30
 * @LastEditTime: 2022-05-01 09:30:39
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/logger.cc
 */
#include "logger.h"

Logger& Logger::GetLogger()
{
    static Logger logger;
    return logger;
}

// 设定日志级别
void Logger::SetLevel(Level level)
{
    m_loglevel = level;
}

Logger::Logger()
{
    // 写日志的线程
    std::thread work([&]()
    {
        for(;;)
        {
            // 获取当前日期，然后取日志信息，写入相应的日志文件中
            time_t now = time(nullptr);
            // 当前时间
            tm* nowtime = localtime(&now);

            char filename[1024] = {0};
            sprintf(filename,"%d-%d-%d-log.txt",
                    nowtime->tm_year+1900,
                    nowtime->tm_mon+1,
                    nowtime->tm_mday);

            // 打开文件
            FILE* fp = fopen(filename,"a+");
            if (fp == nullptr)
            {
                std::cout << "logger file : " << filename << " open error!" << std::endl;
                exit(EXIT_FAILURE);
            }

            std::string msg = logger_queue.pop();

            char time_buf[128] = {0};
            sprintf(time_buf, "%d:%d:%d =>[%s] ", 
                    nowtime->tm_hour, 
                    nowtime->tm_min, 
                    nowtime->tm_sec,
                    (m_loglevel == INFO ? "info" : "error"));

            msg.insert(0, time_buf);
            msg.append("\n");

            fputs(msg.c_str(), fp);
            fclose(fp);
        }
    });
    work.detach();
}
// 写日志
void Logger::log(std::string text)
{
    logger_queue.push(text);
}
