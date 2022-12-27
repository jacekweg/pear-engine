#include "pch.hpp"
#include "utils/logging.hpp"

#include "vertex_buffer.hpp"

#include <glad/glad.h>

namespace Pear
{
	VertexBuffer::VertexBuffer(const float* vertices, const uint32_t size)
	{
		glCreateBuffers(1, &this->render_id);
		glBindBuffer(GL_ARRAY_BUFFER, this->render_id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(const uint32_t size)
	{
		glCreateBuffers(1, &this->render_id);
		glBindBuffer(GL_ARRAY_BUFFER, this->render_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &this->render_id);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->render_id);
	}

	void VertexBuffer::Unbind() const
	{
		ASSERT(this->render_id, "Vertex buffer was not created!")
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
