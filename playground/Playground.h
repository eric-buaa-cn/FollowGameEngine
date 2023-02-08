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
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -1.0f, 1.0f)
    {
        m_VertexArray.reset(hazel::VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
        hazel::Ref<hazel::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
        {
            hazel::BufferLayout layout = {
                {hazel::ShaderDataType::Float3, "a_Position", 0},
                {hazel::ShaderDataType::Float4, "a_Color", 1}};

            vertexBuffer->SetLayout(layout);
        }
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        hazel::Ref<hazel::IndexBuffer> indexBuffer;
        indexBuffer.reset(hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(hazel::VertexArray::Create());

        float squareVertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

        hazel::Ref<hazel::VertexBuffer> squareVB;
        squareVB.reset(hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        {
            hazel::BufferLayout layout = {
                {hazel::ShaderDataType::Float3, "a_Position", 0},
                {hazel::ShaderDataType::Float2, "a_TexCoord", 1}};
            squareVB->SetLayout(layout);
        }
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        hazel::Ref<hazel::IndexBuffer> squareIB;
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

        std::string textureShaderVertexSrc = R"(
            #version 410 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            out vec2 v_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
            }
        )";

        std::string textureShaderFragmentSrc = R"(
            #version 410 core
            
            out vec4 color;

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

            void main()
            {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

        m_TextureShader.reset(hazel::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
        m_TextureCheckerBoard = hazel::Texture2D::Create("playground/assets/textures/Checkerboard.png");
        m_TextureChernoLogo = hazel::Texture2D::Create("playground/assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(hazel::Timestep ts) override
    {
        m_Camera.SetPosition({0.1f, 0.1f, 0.0f});
        m_Camera.SetRotation(0.0f);

        hazel::Renderer::BeginScene(m_Camera);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_flatColorShader)->Bind();
        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_ColorBlue);

        for (int y = -10; y < 10; y++)
        {
            for (int x = -10; x < 10; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                hazel::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
            }
        }

        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_ColorYellow);
        hazel::Renderer::Submit(m_flatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_TextureCheckerBoard->Bind(0);
        m_TextureChernoLogo->Bind(1);

        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<hazel::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 1);
        hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_ColorBlue));
        ImGui::End();
    }

private:
    hazel::OrthographicCamera m_Camera;
    hazel::Ref<hazel::Shader> m_Shader;
    hazel::Ref<hazel::VertexArray> m_VertexArray;

    hazel::Ref<hazel::Shader> m_flatColorShader;
    hazel::Ref<hazel::VertexArray> m_SquareVA;

    hazel::Ref<hazel::Shader> m_TextureShader;
    hazel::Ref<hazel::Texture2D> m_TextureCheckerBoard;
    hazel::Ref<hazel::Texture2D> m_TextureChernoLogo;

    glm::vec3 m_ColorBlue = {0.2f, 0.3f, 0.8f};
    glm::vec3 m_ColorYellow = {0.8f, 0.8f, 0.0f};
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