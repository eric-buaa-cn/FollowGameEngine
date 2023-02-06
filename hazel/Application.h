#pragma once

#include <pch.h>

#include <Window.h>

#include <ApplicationEvent.h>
#include <KeyEvent.h>
#include <MouseEvent.h>

#include <LayerStack.h>
#include <ImguiLayer.h>
#include <Shader.h>

namespace hazel
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event &);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);

        inline const Window &GetWindow() const { return *m_Window; }
        inline static const Application &Get() { return *s_app; }

    private:
        bool OnWindowClose(WindowCloseEvent &);

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        ImGuiLayer *m_ImGuiLayer;

        static const Application *s_app;

        LayerStack m_LayerStack;

        unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

        std::unique_ptr<Shader> m_Shader;
    };

    Application *CreateApplication();
} // namespace hazel
