#include <OpenGLVertexArray.h>

#include <glad/glad.h>

namespace hazel
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
	{
		HZ_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto &element : layout)
		{
			if (!element.Enabled)
			{
				continue;
			}
			glEnableVertexAttribArray(element.AttribIndex);
			glVertexAttribPointer(element.AttribIndex,
								  element.GetComponentCount(),
								  element.ShaderDataTypeToOpenGLBaseType(),
								  element.Normalized ? GL_TRUE : GL_FALSE,
								  layout.GetStride(),
								  (const void *)(intptr_t)element.Offset);
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}