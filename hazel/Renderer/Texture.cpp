#include <Texture.h>

#include <Core.h>
#include <Renderer.h>
#include <OpenGLTexture.h>

namespace hazel
{

    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZ_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
        }

        HZ_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}