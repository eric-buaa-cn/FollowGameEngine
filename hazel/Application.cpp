#include <Application.h>

#include <memory>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <MyLogger.h>

#define BIND_MEM_FUN(c, f) std::bind(&c::f, this, std::placeholders::_1)

namespace hazel
{
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());

        m_Window->SetEventCallback(BIND_MEM_FUN(Application, OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_MEM_FUN(Application, OnWindowClose));
        
        MYLOG_TRACE("{0}", e.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent &)
    {
        m_Running = false;
        return true;
    }

} // namespace hazel
