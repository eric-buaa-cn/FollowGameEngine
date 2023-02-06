#include <RenderCommand.h>

#include <OpenGLRendererAPI.h>

namespace hazel
{

    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}