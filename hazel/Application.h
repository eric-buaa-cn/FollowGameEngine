#pragma once

#include <memory>

#include <Window.h>

#include <ApplicationEvent.h>
#include <KeyEvent.h>
#include <MouseEvent.h>

#include <LayerStack.h>

namespace hazel
{
    class Application {
        public:
            Application();
            virtual ~Application();

            void Run();
            void OnEvent(Event &);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);
        private:
            bool OnWindowClose(WindowCloseEvent &);

        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;

            LayerStack m_LayerStack;
    };

    Application *CreateApplication();
} // namespace hazel
