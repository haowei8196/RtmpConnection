//
//  Util.m
//  anedecodetester
//
//  Created by mac on 13-3-20.
//  Copyright (c) 2013年 Ib. All rights reserved.
//

#include "utils.h"

#ifdef _WIN32
#include "windows.h"
#else
#include <time.h>
#endif // _WIN32

namespace xbase
{
	uint64_t SystemTimeNanos() {
		int64_t ticks;
#if defined(MAC)
		static mach_timebase_info_data_t timebase;
		if (timebase.denom == 0) {
			// Get the timebase if this is the first time we run.
			// Recommended by Apple's QA1398.
			if (mach_timebase_info(&timebase) != KERN_SUCCESS) {
				RTC_DCHECK(false);
			}
		}
		// Use timebase to convert absolute time tick units into nanoseconds.
		ticks = mach_absolute_time() * timebase.numer / timebase.denom;
#elif defined(POSIX)
		struct timespec ts;
		// TODO(deadbeef): Do we need to handle the case when CLOCK_MONOTONIC is not
		// supported?
		clock_gettime(CLOCK_MONOTONIC, &ts);
		ticks = kNumNanosecsPerSec * static_cast<int64_t>(ts.tv_sec) +
			static_cast<int64_t>(ts.tv_nsec);
#elif defined(_WIN32)
		static volatile LONG last_timegettime = 0;
		static volatile int64_t num_wrap_timegettime = 0;
		volatile LONG* last_timegettime_ptr = &last_timegettime;
		DWORD now = timeGetTime();
		// Atomically update the last gotten time
		DWORD old = InterlockedExchange(last_timegettime_ptr, now);
		if (now < old) {
			// If now is earlier than old, there may have been a race between threads.
			// 0x0fffffff ~3.1 days, the code will not take that long to execute
			// so it must have been a wrap around.
			if (old > 0xf0000000 && now < 0x0fffffff) {
				num_wrap_timegettime++;
			}
		}
		ticks = now + (num_wrap_timegettime << 32);
		// TODO(deadbeef): Calculate with nanosecond precision. Otherwise, we're
		// just wasting a multiply and divide when doing Time() on Windows.
		ticks = ticks * kNumNanosecsPerMillisec;
#else
#error Unsupported platform.
#endif
		return ticks;
	}

	int64_t SystemTimeMillis() {
		return static_cast<int64_t>(SystemTimeNanos() / kNumNanosecsPerMillisec);
	}

	uint64_t TimeNanos() {
		return SystemTimeNanos();
	}

	uint32_t Time32() {
		return static_cast<uint32_t>(TimeNanos() / kNumNanosecsPerMillisec);
	}

	int64_t TimeMillis() {
		return static_cast<int64_t>(TimeNanos() / kNumNanosecsPerMillisec);
	}

	uint64_t TimeMicros() {
		return static_cast<uint64_t>(TimeNanos() / kNumNanosecsPerMicrosec);
	}

	int64_t TimeAfter(int64_t elapsed) {
		return TimeMillis() + elapsed;
	}

	int32_t TimeDiff32(uint32_t later, uint32_t earlier) {
		return later - earlier;
	}

	int64_t TimeDiff(int64_t later, int64_t earlier) {
		return later - earlier;
	}
}
