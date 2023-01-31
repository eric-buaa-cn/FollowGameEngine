#include <MyLogger.h>
MYLOG_INIT

#include <Hazel.h>
#include <Playground.h>

hazel::Application *hazel::CreateApplication() {
    return new Playground();
}

#include <EntryPoint.h>