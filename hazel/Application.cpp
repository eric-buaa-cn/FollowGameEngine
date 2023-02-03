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

            for (Layer *layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_MEM_FUN(Application, OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
        
        MYLOG_TRACE("{0}", e.ToString());
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClose(WindowCloseEvent &)
    {
        m_Running = false;
        return true;
    }

} // namespace hazel
