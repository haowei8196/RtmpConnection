
#include "timer.h"
#include <chrono>
#include <thread>
namespace xbase {

    Timer::Timer(int timeout,bool repeat,FunctorPtr task)
    :expired_(true)
    ,try_to_expire_(false)
    ,repeat_(repeat)
    ,timeout_(timeout)
    ,task_(task)
    {
    }
    Timer::Timer(const Timer& t)
    {
        expired_ = t.expired_.load();
        try_to_expire_ = t.try_to_expire_.load();
        repeat_ = t.repeat_.load();
        timeout_ = t.timeout_.load();
        task_ = t.task_;
    }
    Timer::~Timer()
    {
        Invalidate();
    }
    
    void Timer::StartTimer()
    {
        if(expired_ == false)
        {
            return;
        }
        expired_ = false;
        std::thread([this](){
            
            do{
                std::this_thread::sleep_for(std::chrono::milliseconds(timeout_));
                (*task_)();
            }while (repeat_&&!try_to_expire_);
                
            {
                std::lock_guard<std::mutex> locker(mutex_);
                expired_ = true;
                expired_cond_.notify_one();
            }
        }).detach();
    }
    void Timer::Invalidate(){
        if(expired_)
        {
            return;
        }
        if(try_to_expire_)
        {
            return;
        }
        try_to_expire_ = true;
        {
            std::unique_lock<std::mutex> locker(mutex_);
            expired_cond_.wait(locker, [this]{return expired_ == true; });
            if(expired_ == true)
            {
                try_to_expire_ = false;
            }
        }
    }

}
