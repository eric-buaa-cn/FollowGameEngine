#pragma once

#include <MyLogger.h>

#define BIT(x) 1U << x

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { MYLOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }
#else
	#define HZ_ASSERT(x, ...)
#endif