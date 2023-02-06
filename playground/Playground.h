#include <Hazel.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <Shader.h>
#include <OpenGLShader.h>

using ::hazel::Event;
using ::hazel::Layer;

class Layer1 : public Layer
{
public:
    void OnEvent(Event &event) override
    {
        MYLOG_TRACE("{0}", event.ToString());
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("test");
        ImGui::Text("hello world");
        ImGui::End();
    }
};

class ExampleLayer : public Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        m_VertexArray.reset(hazel::VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
        std::shared_ptr<hazel::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
        {
            hazel::BufferLayout layout = {
                {hazel::ShaderDataType::Float3, "a_Position", 0},
                {hazel::ShaderDataType::Float4, "a_Color", 1}};

            vertexBuffer->SetLayout(layout);
        }
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        std::shared_ptr<hazel::IndexBuffer> indexBuffer;
        indexBuffer.reset(hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(hazel::VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};

        std::shared_ptr<hazel::VertexBuffer> squareVB;
        squareVB.reset(hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({{hazel::ShaderDataType::Float3, "a_Position", 0}});
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<hazel::IndexBuffer> squareIB;
        squareIB.reset(hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 410 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec4 v_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        m_Shader.reset(hazel::Shader::Create(vertexSrc, fragmentSrc));

        std::string flatColorShaderVertexSrc = R"(
            #version 410 core
            
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            void main()
            {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
            }
        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 410 core
            
            out vec4 color;

            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_flatColorShader.reset(hazel::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
    }

    void OnUpdate(hazel::Timestep ts) override
    {
        m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
        m_Camera.SetRotation(45.0f);

        hazel::Renderer::BeginScene(m_Camera);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_flatColorShader)->Bind();
        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                hazel::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
            }
        }

        hazel::Renderer::Submit(m_Shader, m_VertexArray);
        hazel::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

private:
    hazel::OrthographicCamera m_Camera;
    std::shared_ptr<hazel::Shader> m_Shader;
    std::shared_ptr<hazel::VertexArray> m_VertexArray;

    std::shared_ptr<hazel::Shader> m_flatColorShader;
    std::shared_ptr<hazel::VertexArray> m_SquareVA;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Playground : public ::hazel::Application
{
public:
    Playground()
    {
        PushLayer(new ExampleLayer());
    }

    ~Playground()
    {
    }
};