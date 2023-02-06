#include "OpenGLContext.h"

#include <MyLogger.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

hazel::OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle)
{
}

void hazel::OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    MYLOG_INFO("OpenGL Info:");
    MYLOG_INFO("  Vendor: {0}", (char *)(glGetString(GL_VENDOR)));
    MYLOG_INFO("  Renderer: {0}", (char *)(glGetString(GL_RENDERER)));
    MYLOG_INFO("  Version: {0}", (char *)(glGetString(GL_VERSION)));
}

void hazel::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
