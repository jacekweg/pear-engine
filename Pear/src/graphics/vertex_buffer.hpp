#pragma once
#include "pch.hpp"

namespace Pear
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const float* vertices, uint32_t size);
		~VertexBuffer();
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) = delete;

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t render_id{};
	};
}
