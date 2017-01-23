#ifndef SESSION_EVENT_H
#define SESSION_EVENT_H


#if defined(WIN32)
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace session {

	class CEvent {
	public:
		static const int kForever = -1;

		CEvent(bool manual_reset, bool initially_signaled);
		~CEvent();

		void Set();
		void Reset();

		// Wait for the CEvent to become signaled, for the specified number of
		// |milliseconds|.  To wait indefinetly, pass kForever.
		bool Wait(int milliseconds);

	private:
#if defined(WIN32)
		HANDLE event_handle_;
#else
		pthread_mutex_t event_mutex_;
		pthread_cond_t event_cond_;
		const bool is_manual_reset_;
		bool event_status_;
#endif
	};

} 


#endif