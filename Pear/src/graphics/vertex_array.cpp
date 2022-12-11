#include "pch.hpp"
#include "utils/logging.hpp"

#include "vertex_array.hpp"

#include <glad/glad.h>


namespace Pear
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &this->render_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &this->render_id);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(this->render_id);
	}

	void VertexArray::Unbind() const
	{
		ASSERT(this->render_id, "No vertex array was bound!")
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& new_vertex_buffer, const GLint size, const GLenum type, const GLboolean normalized, const GLsizei stride, const void* pointer)
	{
		glBindVertexArray(this->render_id);
		new_vertex_buffer->Bind();
		glEnableVertexAttribArray(this->vertex_buffer_idx);

		glVertexAttribPointer(this->vertex_buffer_idx, size, type, normalized, stride, pointer);

		this->vertex_buffer_idx++;
		this->vertex_buffers.emplace_back(new_vertex_buffer);
	}

	void VertexArray::SetIndexBuffer(std::unique_ptr<IndexBuffer>& new_index_buffer)
	{
		glBindVertexArray(this->render_id);
		new_index_buffer->Bind();
		this->index_buffer = std::move(new_index_buffer);
	}
}
