#pragma once
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

#include <glad/glad.h>

namespace Pear
{
	/**
	 * @class VertexArray
	 * @brief This class represents a vertex array object that can be used to store vertex buffer and index buffer.
	 */
	class VertexArray
	{
	public:
		/**
		 * @brief Constructs a VertexArray object.
		 */
		VertexArray();

		/**
		 * @brief Destructs a VertexArray object.
		 */
		~VertexArray();

		// Deleted copy and move constructors and assignment operators
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator=(VertexArray&&) = delete;

		/**
		 * @brief Bind the VertexArray.
		 */
		void Bind() const;
		/**
		 * @brief Unbind the VertexArray.
		 */
		void Unbind() const;

		/**
		 * @brief Add a VertexBuffer to the VertexArray.
		 * @param new_vertex_buffer The VertexBuffer to be added.
		 * @param size The size of the vertex buffer data.
		 * @param type The data type of the vertex buffer data.
		 * @param normalized Whether the data should be normalized.
		 * @param stride The stride of the vertex buffer data.
		 * @param pointer The pointer to the vertex buffer data.
		 */
		void AddVertexBuffer(std::shared_ptr<VertexBuffer>& new_vertex_buffer, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
		/**
		 * @brief Set the IndexBuffer for the VertexArray.
		 * @param new_index_buffer The IndexBuffer to be set.
		 */
		void SetIndexBuffer(std::unique_ptr<IndexBuffer>& new_index_buffer);

		/**
		 * @brief Get the VertexBuffers of the VertexArray.
		 * @return The VertexBuffers of the VertexArray.
		 */
		[[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return this->vertex_buffers; }
		/**
		 * @brief Get the IndexBuffer of the VertexArray.
		 * @return The IndexBuffer of the VertexArray.
		 */
		[[nodiscard]] const std::unique_ptr<IndexBuffer>& GetIndexBuffer() const { return this->index_buffer; }
	private:
		uint32_t render_id{};
		uint32_t vertex_buffer_idx = 0;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
	};
}
