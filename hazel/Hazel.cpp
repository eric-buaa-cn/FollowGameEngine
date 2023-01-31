#include <Hazel.h>

#include <MyLogger.h>

namespace hazel
{
    void print(std::string message) {
        MYLOG_INFO(message);
    }
} // namespace hazel
