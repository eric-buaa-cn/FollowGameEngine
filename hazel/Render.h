#pragma once

#include <RendererAPI.h>

namespace hazel
{

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        // After the bind of program, submit vertex array to draw.
        static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API GetAPI()
        {
            return RendererAPI::GetAPI();
        }
    };

}
