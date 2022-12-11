#pragma once

#include "pch.hpp"

#include <glad/glad.h>

namespace Pear
{
	class Texture
	{
	public:
		explicit Texture(const std::string& src);
		explicit Texture(void* data);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(Texture&&) = delete;

		[[nodiscard]] uint32_t GetWidth() const { return this->width; }
		[[nodiscard]] uint32_t GetHeight() const { return this->height; }

		void Bind(uint32_t slot) const;
	private:
		std::string src_path;
		GLsizei width, height;
		uint32_t render_id{};
		GLenum external_format{}, internal_format{};
	};
}
