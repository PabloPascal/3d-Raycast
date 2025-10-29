#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>


class ThreadPool
{
public:
    ThreadPool(size_t thread_count)
    {

        for(size_t i = 0; i < thread_count; i++)
        {
            threads.emplace_back([this]
                {
                    while(true)
                    {   
                        std::function<void()> task;
                        
                        {
                            std::unique_lock<std::mutex> lock(mx);
                            condition.wait(lock, [this]{return finish || !tasks.empty();});
                            if(finish && tasks.empty()) return;

                            task = std::move( tasks.front() );
                            tasks.pop();
                        }

                        task();

                    }



                }
            );
        }


    }

    template <typename U>
    void add_task(U&& task)
    {
        {
            std::unique_lock<std::mutex> lock(mx);
            tasks.emplace(std::forward<U>(task));
        }
        condition.notify_one();
    }


    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mx);
            finish = true;
        }
        condition.notify_all();


        for(auto& thread : threads)
        {   
            thread.join();
        }

    }

private:

    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mx;

    std::condition_variable condition;
    bool finish = false;

};


#endif 