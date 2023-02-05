#include "OpenGLContext.h"

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
}

void hazel::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
