#pragma once

/*
Control the log level at compile time.
*/
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

/*
Usage:

1. Put the following in your main source file.
#include <MyLogger.h>
MYLOG_INIT

2. Call log macros.
MYLOG_INFO("hello world");
MYLOG_INFO("your name is {} and {} years old", "jack", 10);

*/
class MyLogger
{
public:
    MyLogger();
};

#define MYLOG_INIT MyLogger ini;

#define MYLOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define MYLOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define MYLOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define MYLOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define MYLOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)