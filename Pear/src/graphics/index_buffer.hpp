#pragma once
#include "pch.hpp"

namespace Pear
{
	/**
	 * @class IndexBuffer
	 * @brief A class representing an index buffer.
	 */
	class IndexBuffer
	{
	public:
		/**
		 * @brief Constructs an IndexBuffer object.
		 * @param indices Pointer to the array of indices.
		 * @param count Number of indices in the array.
		 */
		IndexBuffer(const uint32_t* indices, uint32_t count);
		/**
		 * @brief Destructor for the IndexBuffer class.
		 */
		~IndexBuffer();

		// Deleted copy and move constructors and assignment operators
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) = delete;
		IndexBuffer& operator=(IndexBuffer&&) = delete;

		/**
		 * @brief Binds the index buffer.
		 */
		void Bind() const;
		/**
		 * @brief Unbinds the index buffer.
		 */
		void Unbind() const;

		/**
		 * @brief Gets the number of indices in the buffer.
		 * @return The number of indices.
		 */
		[[nodiscard]] uint32_t GetCount() const { return this->count; }
	private:
		/**
		 * @brief The render ID of the index buffer.
		 */
		uint32_t render_id{};
		/**
		 * @brief The number of indices in the buffer.
		 */
		uint32_t count{};
	};
}
