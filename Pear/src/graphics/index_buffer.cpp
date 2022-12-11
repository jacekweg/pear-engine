#include "pch.hpp"
#include "utils/logging.hpp"

#include "index_buffer.hpp"

#include <glad/glad.h>

namespace Pear
{
	IndexBuffer::IndexBuffer(const uint32_t* indices, const uint32_t count)
		:count(count)
	{
		glCreateBuffers(1, &this->render_id);
		glBindBuffer(GL_ARRAY_BUFFER, this->render_id);
		const auto size = static_cast<GLintptr>(count * sizeof(uint32_t));
		glBufferData(GL_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &this->render_id);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->render_id);
	}

	void IndexBuffer::Unbind() const
	{
		ASSERT(this->render_id, "No index buffer was bound")
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
