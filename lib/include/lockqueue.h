/*
 * @Author: your name
 * @Date: 2022-04-29 20:12:55
 * @LastEditTime: 2022-04-29 22:47:42
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /linux/RPC/src/include/lockqueue.h
 */
#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<class T>
class Lockqueue
{
public:
    void push(T val)
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        m_lockqueue.push(val);
        m_condition_variable.notify_one();
    }
    T pop()
    {
        while(m_lockqueue.empty())
        {
            std::unique_lock<std::mutex> lk(m_mutex);
            m_condition_variable.wait(lk);
        }
        T val = m_lockqueue.front();
        m_lockqueue.pop();
        return val;
    }
private:
    std::queue<T> m_lockqueue;
    std::mutex m_mutex;
    std::condition_variable m_condition_variable;  
};