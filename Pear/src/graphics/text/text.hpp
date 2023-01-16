#pragma once

#include "pch.hpp"

#include "graphics/shader.hpp"
#include "graphics/vertex_array.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Pear
{
	/**
	 * @class Text
	 * @brief The Text class for handling text rendering in the Pear engine.
	 */
	class Text
	{
	public:
		/**
		 * @brief Initializes the text rendering subsystem.
		 */
		static void Start();
		/**
		 * @brief Renders text on screen.
		 * @param text The text to be rendered.
		 * @param pos The position of the text on screen.
		 * @param scale The scale of the text.
		 * @param color The color of the text.
		 */
		static void Render(const std::string& text, const glm::vec2& pos, float scale, const glm::vec3& color);
	private:
		/**
		 * @struct Character
		 * @brief The character information for a specific character.
		 */
		struct Character {
			uint32_t texture_id;
			glm::ivec2 size;
			glm::ivec2 bearing;
			uint32_t advance;
		};
		/**
		 * @brief A map of characters and their associated character information
		 */
		inline static std::map<char, Character> characters;

		/**
		 * @brief The shader used for rendering text.
		 */
		inline static std::unique_ptr<Shader> text_shader;
		/**
		 * @brief The vertex array used for rendering text.
		 */
		inline static std::unique_ptr<VertexArray> text_vertex_array;
		/**
		 * @brief The vertex buffer used for rendering text.
		 */
		inline static std::shared_ptr<VertexBuffer> text_vb;
	};
}
