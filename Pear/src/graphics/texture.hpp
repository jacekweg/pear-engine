#pragma once

#include "pch.hpp"

#include <glad/glad.h>

namespace Pear
{
	/**
	 * @class Texture
	 * @brief This class represents a texture object that can be bound to a slot and used in rendering.
	 */
	class Texture
	{
	public:
		/**
		 * @brief Constructs a Texture object from a file path.
		 * @param src The file path of the texture.
		 */
		explicit Texture(const std::string& src);
		/**
		 * @brief Constructs a Texture object from a pointer to raw data.
		 * @param data Pointer to the raw data of the texture.
		 */
		explicit Texture(void* data);
		/**
		 * @brief Destructs a Texture object.
		 */
		~Texture();

		// Deleted copy and move constructors and assignment operators
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(Texture&&) = delete;

		/**
		 * @brief Get the width of the Texture.
		 * @return The width of the Texture.
		 */
		[[nodiscard]] uint32_t GetWidth() const { return this->width; }
		/**
		 * @brief Get the height of the Texture.
		 * @return The height of the Texture.
		 */
		[[nodiscard]] uint32_t GetHeight() const { return this->height; }

		/**
		 * @brief Bind the Texture to a slot.
		 * @param slot The slot to bind the Texture to.
		 */
		void Bind(uint32_t slot) const;
	private:
		std::string src_path;
		GLsizei width, height;

		uint32_t render_id{};
		GLenum external_format{}, internal_format{};
	};
}
