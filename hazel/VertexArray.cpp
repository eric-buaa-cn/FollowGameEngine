#include <VertexArray.h>
#include <OpenGLVertexArray.h>

#include <Core.h>
#include <Render.h>

namespace hazel
{

    VertexArray *VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            HZ_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
        }

        HZ_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}