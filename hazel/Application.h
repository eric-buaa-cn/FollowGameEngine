#pragma once

#include <memory>

#include <Window.h>

namespace hazel
{
    class Application {
        public:
            Application();
            virtual ~Application();

            virtual void Run();
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };

    Application *CreateApplication();
} // namespace hazel
