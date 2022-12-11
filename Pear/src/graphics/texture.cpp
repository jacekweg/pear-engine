#include "pch.hpp"

#include "texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

namespace Pear
{
	Texture::Texture(const std::string& src)
		:src_path(src)
	{
		int new_width, new_height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(src.c_str(), &new_width, &new_height, &channels, 0);

		this->width = new_width;
		this->height = new_height;

		if(channels == 4)
		{
			this->external_format = GL_RGBA;
			this->internal_format = GL_RGBA8;
		}
		else if(channels == 3)
		{
			this->external_format = GL_RGB;
			this->internal_format = GL_RGB8;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &this->render_id);
		glTextureStorage2D(this->render_id, 1, this->internal_format, this->width, this->height);

		glTextureParameteri(this->render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->render_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->render_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(this->render_id, 0, 0, 0, this->width, this->height, this->external_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	Texture::Texture(void* data)
	{
		this->width = 1;
		this->height = 1;
		this->external_format = GL_RGBA;
		this->internal_format = GL_RGBA8;

		glCreateTextures(GL_TEXTURE_2D, 1, &this->render_id);
		glTextureStorage2D(this->render_id, 1, this->internal_format, this->width, this->height);

		glTextureParameteri(this->render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->render_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->render_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(this->render_id, 0, 0, 0, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->render_id);
	}

	void Texture::Bind(const uint32_t slot) const
	{
		glBindTextureUnit(slot, this->render_id);
	}
}
