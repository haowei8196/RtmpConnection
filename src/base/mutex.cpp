#include "mutex.h"

namespace session {

	CMutex::CMutex()
	{
#if defined(_WIN32)
		InitializeCriticalSection(&crit_);
#else
		pthread_mutexattr_t mutex_attribute;
		pthread_mutexattr_init(&mutex_attribute);
		pthread_mutexattr_settype(&mutex_attribute, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex_, &mutex_attribute);
		pthread_mutexattr_destroy(&mutex_attribute);
#endif
	}
	CMutex::~CMutex()
	{
#if defined(_WIN32)
		DeleteCriticalSection(&crit_);
#else
		pthread_mutex_destroy(&mutex_);
#endif
	}
	void CMutex::Enter()
	{
#if defined(_WIN32)
		EnterCriticalSection(&crit_);
#else
		pthread_mutex_lock(&mutex_);
#endif
	}
	void CMutex::Leave()
	{
#if defined(_WIN32)
		LeaveCriticalSection(&crit_);
#else
		pthread_mutex_unlock(&mutex_);
#endif
	}
	CAutoLock::CAutoLock(CMutex* mute):mute_(mute)
	{
		mute_->Enter();
	}
	CAutoLock::~CAutoLock()
	{
		mute_->Leave();
	}
}