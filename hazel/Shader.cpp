#include <Shader.h>

#include <Core.h>
#include <MyLogger.h>
#include <Renderer.h>
#include <OpenGLShader.h>

namespace hazel
{
    Shader *Shader::Create(const std::string &filePath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZ_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(filePath);
        }

        HZ_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZ_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        HZ_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}