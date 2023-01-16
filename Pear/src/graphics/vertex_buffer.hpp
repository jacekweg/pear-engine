#pragma once
#include "pch.hpp"

namespace Pear
{
	/**
	 * @class VertexBuffer
	 * @brief This class represents a vertex buffer object that can be used to store vertex data.
	 */
	class VertexBuffer
	{
	public:
		/**
		 * @brief Constructs a VertexBuffer object from a pointer to vertex data.
		 * @param vertices Pointer to the vertex data.
		 * @param size The size of the vertex data in bytes.
		 */
		VertexBuffer(const float* vertices, uint32_t size);
		/**
		 * @brief Constructs a VertexBuffer object with a specified size.
		 * @param size The size of the vertex buffer in bytes.
		 */
		explicit VertexBuffer(uint32_t size);
		/**
		 * @brief Destructs a VertexBuffer object.
		 */
		~VertexBuffer();

		// Deleted copy and move constructors and assignment operators
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) = delete;

		/**
		 * @brief Bind the VertexBuffer.
		 */
		void Bind() const;
		/**
		 * @brief Unbind the VertexBuffer.
		 */
		void Unbind() const;
	private:
		uint32_t render_id{};
	};
}
