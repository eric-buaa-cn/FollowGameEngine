#include <Application.h>

#include <MyLogger.h>
MYLOG_INIT

/*
EntryPoint.h is the entry point for client easy to use.
*/

int main() {
    // hazel::CreateApplication should be defined in the client side.
    auto app = hazel::CreateApplication();
    app->Run();
    delete app;
    return 0;
}