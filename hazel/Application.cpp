#include <Application.h>

#include <MyLogger.h>

namespace hazel
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        MYLOG_INFO("this is the default application run logic. Please override it with your own logic.");
    }

} // namespace hazel
