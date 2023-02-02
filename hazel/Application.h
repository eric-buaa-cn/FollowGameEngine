#pragma once

#include <memory>

#include <Window.h>

#include <ApplicationEvent.h>
#include <KeyEvent.h>
#include <MouseEvent.h>

namespace hazel
{
    class Application {
        public:
            Application();
            virtual ~Application();

            void Run();
            void OnEvent(Event &);
        private:
            bool OnWindowClose(WindowCloseEvent &);

        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };

    Application *CreateApplication();
} // namespace hazel
