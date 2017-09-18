#ifndef BASE_TIMER_H
#define BASE_TIMER_H

#include "functor.h"

#include <atomic>
#include <mutex>
#include <condition_variable>

namespace xbase {
    class Timer{
    public:
        Timer(int timeout,bool repeat,FunctorPtr task);
        Timer(const Timer& t);
        ~Timer();
        void StartTimer();
        void Invalidate();
    private:
        std::atomic<bool> expired_;
        std::atomic<bool> try_to_expire_;
        std::atomic<bool> repeat_;
        std::atomic<int>  timeout_;
        std::mutex mutex_;
        std::condition_variable expired_cond_;
        FunctorPtr task_;
    };
}
#endif

