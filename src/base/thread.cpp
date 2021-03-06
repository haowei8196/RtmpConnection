#include "thread.h"
#include "utils.h"
#ifdef _ANDROID
#include <sys/prctl.h>
#endif
#ifndef __has_feature
#define __has_feature(x) 0  // Compatibility with non-clang or LLVM compilers.
#endif  // __has_feature
namespace xbase {
	Thread::Thread()
		:running_(true,false)
#if defined(_WIN32)
		,thread_(NULL)
		,thread_id_(0)
#endif
	{
		SetName("Thread", this);
	}

	Thread::~Thread()
	{
	}
	bool Thread::Start()
	{
		if (running()) return false;

#if defined(_WIN32)
		thread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PreRun, this, 0,
			&thread_id_);
		if (thread_) {
			running_.Set();
		}
		else {
			return false;
		}
#else
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		int error_code = pthread_create(&thread_, &attr, PreRun, this);
		if (0 != error_code) {
			//LOG(LS_ERROR) << "Unable to create pthread, error " << error_code;
			return false;
		}
		running_.Set();
#endif
		return true;
	}
	void Thread::Stop()
	{
		if (running()) {
            Mq::Quit();
#if defined(_WIN32)
			WaitForSingleObject(thread_, INFINITE);
			CloseHandle(thread_);
			thread_ = NULL;
			thread_id_ = 0;
#else
			void *pv;
			pthread_join(thread_, &pv);
#endif
			running_.Reset();
		}
	}
	bool Thread::SleepMs(int milliseconds)
	{
#if defined(_WIN32)
		::Sleep(milliseconds);
		return true;
#else
		// POSIX has both a usleep() and a nanosleep(), but the former is deprecated,
		// so we use nanosleep() even though it has greater precision than necessary.
		struct timespec ts;
		ts.tv_sec = milliseconds / 1000;
		ts.tv_nsec = (milliseconds % 1000) * 1000000;
		int ret = nanosleep(&ts, NULL);
		if (ret != 0) {
			//LOG_ERR(LS_WARNING) << "nanosleep() returning early";
			return false;
		}
		return true;
#endif
	}
	bool Thread::running()
	{ 
		return running_.Wait(0); 
	}
	bool Thread::SetName(const std::string& name, const void* obj)
	{
		if (running()) return false;
		name_ = name;
		if (obj) {
			char buf[16];
			sprintf(buf," 0x%p", obj);
			name_ += buf;
		}
		return true;
	}
	void* Thread::PreRun(void* pv) {
		Thread* thread = static_cast<Thread*>(pv);
        const char* name = thread->name_.c_str();
#if defined(_WIN32)
        struct {
            DWORD dwType;
            LPCSTR szName;
            DWORD dwThreadID;
            DWORD dwFlags;
        } threadname_info = {0x1000, name, static_cast<DWORD>(-1), 0};
        
        __try {
            ::RaiseException(0x406D1388, 0, sizeof(threadname_info) / sizeof(DWORD),
                             reinterpret_cast<ULONG_PTR*>(&threadname_info));
        } __except (EXCEPTION_EXECUTE_HANDLER) {
        }
#elif defined(_ANDROID)
        prctl(PR_SET_NAME, reinterpret_cast<unsigned long>(name));
#elif defined(_IOS)
        pthread_setname_np(name);
#endif
        
        
#if __has_feature(objc_arc)
		@autoreleasepool
#endif
		{
			thread->Run();
			return NULL;
		}
	}
	void Thread::Run()
	{
		ProcessMessages(CEvent::kForever);
	}

	Mq::Mq()
		:event_(false,false)
		,quit_(false)
	{
	}
	Mq::~Mq()
	{
	}
	int Mq::PutQ(FunctorPtr fn)
	{
		{
			CAutoLock lock(&mutex_);

			if (quit_)
			{
				return (unsigned int)-1;
			}
			msgq_.push_back(fn);
			event_.Set();
		}

		if (fn.getPtr())
			fn->Wait();
		return 0;
	}
	FunctorPtr Mq::GetQ()
	{
		FunctorPtr fn;
		CAutoLock lock(&mutex_);
		if (!msgq_.empty())
		{
			fn = msgq_.front();
			if (fn.getPtr())
				msgq_.pop_front();
		}
		return fn;
	}
	void Mq::Quit()
	{
		quit_ = true;
		event_.Set();
	}
	bool Mq::ProcessMessages(int cmsLoop) {
		int64_t msEnd = (CEvent::kForever == cmsLoop) ? 0 : TimeAfter(cmsLoop);
		int cmsNext = cmsLoop;
		FunctorPtr fn;
		do
		{
			fn = GetQ();
			if (fn.getPtr())
			{
				(*fn)();
				fn->Signal();
			}
			if (cmsLoop != CEvent::kForever) {
				cmsNext = static_cast<int>(TimeUntil(msEnd));
				if (cmsNext < 0)
					return true;
			}
			if (!fn.getPtr())
			{
				event_.Wait(cmsLoop == CEvent::kForever?CEvent::kForever:cmsNext);
			}
		} while (!quit_);
		return true;
	}
}
