#ifndef BASE_UTILS_H
#define BASE_UTILS_H
#include <stdint.h>
#include <string>
#include <sstream>
#define UNUSED(arg) (void)arg

#ifdef _IOS
#define GETDICINT(dic, key,v) \
id value =[dic objectForKey:key];\
if ([value isKindOfClass:[NSString class]]||[value isKindOfClass:[NSNumber class]])\
{\
    v = [value intValue];\
}\
else\
{\
    v = 0;\
}
#define CreateCFDictionary(keys,values,size ) CFDictionaryCreate(NULL, keys, values, size,&kCFTypeDictionaryKeyCallBacks,&kCFTypeDictionaryValueCallBacks);

#define UNUSED(arg) (void)arg
#endif

#define Big2Little32(A)   ((( (uint32_t)(A) & 0xff000000) >> 24) | \
(( (uint32_t)(A) & 0x00ff0000) >> 8)   | \
(( (uint32_t)(A) & 0x0000ff00) << 8)   | \
(( (uint32_t)(A) & 0x000000ff) << 24))

namespace xbase {
	static const int64_t kNumMillisecsPerSec = INT64_C(1000);
	static const int64_t kNumMicrosecsPerSec = INT64_C(1000000);
	static const int64_t kNumNanosecsPerSec = INT64_C(1000000000);

	static const int64_t kNumMicrosecsPerMillisec =
		kNumMicrosecsPerSec / kNumMillisecsPerSec;
	static const int64_t kNumNanosecsPerMillisec =
		kNumNanosecsPerSec / kNumMillisecsPerSec;
	static const int64_t kNumNanosecsPerMicrosec =
		kNumNanosecsPerSec / kNumMicrosecsPerSec;

    
    

	// Returns the actual system time, even if a clock is set for testing.
	// Useful for timeouts while using a test clock, or for logging.
	uint64_t SystemTimeNanos();
	int64_t SystemTimeMillis();

	// Returns the current time in milliseconds in 32 bits.
	uint32_t Time32();

	// Returns the current time in milliseconds in 64 bits.
	int64_t TimeMillis();
	// Deprecated. Do not use this in any new code.
	inline int64_t Time() {
		return TimeMillis();
	}

	// Returns the current time in microseconds.
	uint64_t TimeMicros();

	// Returns the current time in nanoseconds.
	uint64_t TimeNanos();

	// Returns a future timestamp, 'elapsed' milliseconds from now.
	int64_t TimeAfter(int64_t elapsed);

	// Number of milliseconds that would elapse between 'earlier' and 'later'
	// timestamps.  The value is negative if 'later' occurs before 'earlier'.
	int64_t TimeDiff(int64_t later, int64_t earlier);
	int32_t TimeDiff32(uint32_t later, uint32_t earlier);

	// The number of milliseconds that have elapsed since 'earlier'.
	inline int64_t TimeSince(int64_t earlier) {
		return TimeMillis() - earlier;
	}

	// The number of milliseconds that will elapse between now and 'later'.
	inline int64_t TimeUntil(uint64_t later) {
		return later - TimeMillis();
	}
    
    template <class T>
    std::string ToString(const T& t)
    {
        std::ostringstream ss;
        ss << t;
        return ss.str();
    }
    template <class T>
    int ToNumber(const std::string s,T& t)
    {
        std::stringstream a;
        a<<s;
        a>>t;
        return 0;
    }
}
#endif
