#include <Application.h>

#include <pch.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core.h>
#include <MyLogger.h>

#include <Buffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <RenderCommand.h>

#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

namespace hazel
{
    const Application *Application::s_app = nullptr;

    Application::Application()
    {
        s_app = this;
        m_Window = std::unique_ptr<Window>(Window::Create());

        m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushLayer(m_ImGuiLayer);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            RenderCommand::SetClearColor({0.12f, 0.12f, 0.12f, 1.0f});
            RenderCommand::Clear();

            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->RenderBegin();
            for (Layer *layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->RenderEnd();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }

        // MYLOG_TRACE("{0}", e.ToString());
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClose(WindowCloseEvent &)
    {
        m_Running = false;
        return true;
    }

} // namespace hazel
