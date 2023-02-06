#include <VertexArray.h>
#include <OpenGLVertexArray.h>

#include <Core.h>
#include <Renderer.h>

namespace hazel
{

    VertexArray *VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZ_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexArray();
        }

        HZ_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}