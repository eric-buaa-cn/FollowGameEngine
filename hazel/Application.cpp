#include <Application.h>

#include <pch.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core.h>
#include <MyLogger.h>

#include <Buffer.h>
#include <VertexArray.h>
#include <Render.h>
#include <RenderCommand.h>

#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

namespace hazel
{
    const Application *Application::s_app = nullptr;

    Application::Application()
        : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        s_app = this;
        m_Window = std::unique_ptr<Window>(Window::Create());

        m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushLayer(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        {
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position", 0},
                {ShaderDataType::Float4, "a_Color", 1}};

            vertexBuffer->SetLayout(layout);
        }
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f};

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({{ShaderDataType::Float3, "a_Position", 0}});
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 410 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec4 v_Color;

            uniform mat4 u_ViewProjection;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 410 core
            
            out vec4 v_FragColor;

            in vec4 v_Color;

            void main()
            {
                v_FragColor = v_Color;
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 410 core
            
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            void main()
            {
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 410 core
            
            out vec4 color;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor({0.12f, 0.12f, 0.12f, 1.0f});
            RenderCommand::Clear();

            m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
            m_Camera.SetRotation(45.0f);

            Renderer::BeginScene(m_Camera);
            Renderer::Submit(m_BlueShader, m_SquareVA);
            Renderer::Submit(m_Shader, m_VertexArray);
            Renderer::EndScene();

            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->RenderBegin();
            for (Layer *layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->RenderEnd();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }

        // MYLOG_TRACE("{0}", e.ToString());
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClose(WindowCloseEvent &)
    {
        m_Running = false;
        return true;
    }

} // namespace hazel
