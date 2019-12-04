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
    bool stop;

public:


    explicit ThreadPool(size_t poolSize): poolSize_(poolSize), stop(false){
        for (size_t i = 0; i < poolSize_; i++){
            threads_.emplace_back([this]()
            {
                for(;;)
                {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(this->m_);
                        this->hasTask_.wait(lock,
                            [this](){ return this->stop || !this->taskQueue_.empty(); });
                        if(this->stop && this->taskQueue_.empty())
                            return;
                        task = std::move(this->taskQueue_.front());
                        this->taskQueue_.pop();
                    }
                    task();
                }
            });
        }
    }

   
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
        using return_type = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<return_type()>> (std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

        auto ff = [task](){ (*task)() ;};
        {
            std::unique_lock<std::mutex> lock(m_);
            taskQueue_.emplace(ff);
        }
        hasTask_.notify_one();
        return task->get_future();
    }


    ~ThreadPool(){
        {
            std::unique_lock<std::mutex> lock(m_);
            stop = true;
        }
        hasTask_.notify_all();
        for(size_t i = 0; i < poolSize_; i++){
            threads_[i].join();
        }
    }

};