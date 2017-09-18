#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include "event.h"
#include <string>
#include "autoptr.h"
#include "functor.h"
#include "mutex.h"
#include <list>
namespace xbase {
	class Mq
	{
	public:
		Mq();
		virtual ~Mq();

		int PutQ(FunctorPtr fn);
		FunctorPtr GetQ();

		void Quit();

		bool ProcessMessages(int cmdmis);
	private:
		CEvent event_;
		CMutex mutex_;
		typedef std::list<FunctorPtr> MessageList;
		MessageList msgq_;
		bool quit_;
	};
	class Thread:public Mq
	{
	public:
		Thread();
		virtual ~Thread();
	public:
		virtual bool Start();
		virtual void Stop();

		static bool SleepMs(int ms);
		bool SetName(const std::string& name , const void* obj);
		virtual void Run();
	protected:
		bool running();
	private:
		static void *PreRun(void *pv);
	private:
		std::string name_;
		CEvent running_;
#if defined(_WIN32)
		HANDLE thread_;
		DWORD thread_id_;
#else
		pthread_t thread_;
#endif
	};

	
}
#endif
