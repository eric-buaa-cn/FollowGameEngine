#pragma once

namespace hazel
{
    class Application {
        public:
            Application();
            virtual ~Application();

            virtual void Run();
    };

    Application *CreateApplication();
} // namespace hazel
