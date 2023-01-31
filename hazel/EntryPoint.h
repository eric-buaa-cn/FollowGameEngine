#include <Application.h>

/*
EntryPoint.h is the entry point for client easy to use.
*/

int main() {
    auto app = hazel::CreateApplication();
    app->Run();
    delete app;
    return 0;
}