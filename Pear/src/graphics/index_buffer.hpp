#pragma once
#include "pch.hpp"

namespace Pear
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const uint32_t* indices, uint32_t count);
		~IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) = delete;
		IndexBuffer& operator=(IndexBuffer&&) = delete;

		void Bind() const;
		void Unbind() const;

		[[nodiscard]] uint32_t GetCount() const { return this->count; }
	private:
		uint32_t render_id{};
		uint32_t count{};
	};
}
