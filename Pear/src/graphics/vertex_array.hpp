#pragma once
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

#include <glad/glad.h>

namespace Pear
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator=(VertexArray&&) = delete;

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(std::shared_ptr<VertexBuffer>& new_vertex_buffer, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
		void SetIndexBuffer(std::unique_ptr<IndexBuffer>& new_index_buffer);

		[[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return this->vertex_buffers; }
		[[nodiscard]] const std::unique_ptr<IndexBuffer>& GetIndexBuffer() const { return this->index_buffer; }
	private:
		uint32_t render_id{};
		uint32_t vertex_buffer_idx = 0;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
	};
}
