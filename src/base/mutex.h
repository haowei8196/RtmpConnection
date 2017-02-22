#ifndef SESSION_MUTE_H
#define SESSION_MUTE_H

#if defined(_WIN32)
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace session {
	class CMutex {
	public:
		CMutex();
		~CMutex();

		void Enter();
		void Leave();
	private:
#if defined(_WIN32)
		mutable CRITICAL_SECTION crit_;
#else
		mutable pthread_mutex_t mutex_;
#endif
	};

	class CAutoLock {
	public:
		CAutoLock(CMutex* mute);
		~CAutoLock();
	private:
		CMutex* mute_;
	};
}
#endif