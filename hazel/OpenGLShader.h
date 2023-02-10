#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#include <Shader.h>
#include <glad/glad.h>

namespace hazel
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &filePath);
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        void UploadUniformInt(const std::string &name, int value);
        void UploadUniformFloat(const std::string &name, float value);
        void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);
        void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);
        void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

        void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
        void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

    private:
        std::string ReadFile(const std::string &filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
        void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

    private:
        uint32_t m_RendererID;
    };

}