#pragma once

#include <GraphicsContext.h>

struct GLFWwindow;

namespace hazel
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow *windowHandle);
        ~OpenGLContext() = default;

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };
} // namespace hazel
