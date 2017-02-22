
#include "event.h"

#if defined(_WIN32)
#include <windows.h>
#else
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#endif

namespace session {

#if defined(_WIN32)

	CEvent::CEvent(bool manual_reset, bool initially_signaled) {
		event_handle_ = ::CreateEvent(NULL,                 // Security attributes.
			manual_reset,
			initially_signaled,
			NULL);                // Name.
	}

	CEvent::~CEvent() {
		CloseHandle(event_handle_);
	}

	void CEvent::Set() {
		SetEvent(event_handle_);
	}

	void CEvent::Reset() {
		ResetEvent(event_handle_);
	}

	bool CEvent::Wait(int milliseconds) {
		DWORD ms = (milliseconds == kForever) ? INFINITE : milliseconds;
		return (WaitForSingleObject(event_handle_, ms) == WAIT_OBJECT_0);
	}

#else

	CEvent::CEvent(bool manual_reset, bool initially_signaled)
		: is_manual_reset_(manual_reset),
		event_status_(initially_signaled) {
	}

	CEvent::~CEvent() {
		pthread_mutex_destroy(&event_mutex_);
		pthread_cond_destroy(&event_cond_);
	}

	void CEvent::Set() {
		pthread_mutex_lock(&event_mutex_);
		event_status_ = true;
		pthread_cond_broadcast(&event_cond_);
		pthread_mutex_unlock(&event_mutex_);
	}

	void CEvent::Reset() {
		pthread_mutex_lock(&event_mutex_);
		event_status_ = false;
		pthread_mutex_unlock(&event_mutex_);
	}

	bool CEvent::Wait(int milliseconds) {
		int error = 0;

		struct timespec ts;
		if (milliseconds != kForever) {
			// Converting from seconds and microseconds (1e-6) plus
			// milliseconds (1e-3) to seconds and nanoseconds (1e-9).

#if HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE
			// Use relative time version, which tends to be more efficient for
			// pthread implementations where provided (like on Android).
			ts.tv_sec = milliseconds / 1000;
			ts.tv_nsec = (milliseconds % 1000) * 1000000;
#else
			struct timeval tv;
			gettimeofday(&tv, NULL);

			ts.tv_sec = tv.tv_sec + (milliseconds / 1000);
			ts.tv_nsec = tv.tv_usec * 1000 + (milliseconds % 1000) * 1000000;

			// Handle overflow.
			if (ts.tv_nsec >= 1000000000) {
				ts.tv_sec++;
				ts.tv_nsec -= 1000000000;
			}
#endif
		}

		pthread_mutex_lock(&event_mutex_);
		if (milliseconds != kForever) {
			while (!event_status_ && error == 0) {
#if HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE
				error = pthread_cond_timedwait_relative_np(
					&event_cond_, &event_mutex_, &ts);
#else
				error = pthread_cond_timedwait(&event_cond_, &event_mutex_, &ts);
#endif
			}
		}
		else {
			while (!event_status_ && error == 0)
				error = pthread_cond_wait(&event_cond_, &event_mutex_);
		}

		// NOTE(liulk): Exactly one thread will auto-reset this CEvent. All
		// the other threads will think it's unsignaled.  This seems to be
		// consistent with auto-reset events in WEBRTC_WIN
		if (error == 0 && !is_manual_reset_)
			event_status_ = false;

		pthread_mutex_unlock(&event_mutex_);

		return (error == 0);
	}

#endif

} 
