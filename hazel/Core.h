#pragma once

#include <memory>
#include <MyLogger.h>

#define BIT(x) 1U << x

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...)                                      \
    {                                                          \
        if (!(x))                                              \
        {                                                      \
            MYLOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            __builtin_trap();                                  \
        }                                                      \
    }
#else
#define HZ_ASSERT(x, ...)
#endif

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace hazel
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;
}