#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

using Task = std::function<void ()>;

class ThreadPool
{
    size_t poolSize_;
    std::condition_variable hasTask_;
    std::queue<Task> taskQueue_;
    std::vector<std::thread> threads_;
    std::mutex m_;
    std::atomic<bool> stop;

public:


    explicit ThreadPool(size_t poolSize): poolSize_(poolSize), stop(false){
        for (size_t i = 0; i < poolSize_; i++){
            threads_.emplace_back([this]()
            {
                for(;;)
                {
                    std::unique_lock<std::mutex> lock(m_);
                    if (!taskQueue_.empty()){
                        auto task = std::move(taskQueue_.front());
                        taskQueue_.pop();
                        lock.unlock();
                        task();
                    }
                    else{
                        if (!stop) hasTask_.wait(lock);
                        else return;
                    }
                }
            });
        }
    }

   
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
        using return_type = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<return_type()>> (std::bind(func, args...));

        auto ff = [task](){ (*task)() ;};
        {
            std::unique_lock<std::mutex> lock(m_);
            taskQueue_.emplace(ff);
        }
        hasTask_.notify_one();
        return task->get_future();
    }


    ~ThreadPool(){
        stop = true;
        hasTask_.notify_all();
        for(size_t i = 0; i < poolSize_; i++){
            threads_[i].join();
        }
    }

};