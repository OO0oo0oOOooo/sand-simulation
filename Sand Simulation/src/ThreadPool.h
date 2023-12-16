#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count = std::thread::hardware_concurrency())
    {
        if (!thread_count)
            return;
    }

    ~ThreadPool()
    {

    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(const ThreadPool&&) = delete;
    ThreadPool& operator = (const ThreadPool&) = delete;
    ThreadPool& operator = (ThreadPool&&) = delete;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};