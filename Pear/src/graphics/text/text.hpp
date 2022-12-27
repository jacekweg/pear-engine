#pragma once

#include "pch.hpp"

#include "graphics/shader.hpp"
#include "graphics/vertex_array.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Pear
{
	class Text
	{
	public:
		static void Start();
		static void Render(const std::string& text, const glm::vec2& pos, float scale, const glm::vec3& color);
	private:
		struct Character {
			uint32_t texture_id;
			glm::ivec2 size;
			glm::ivec2 bearing;
			uint32_t advance;
		};
		inline static std::map<char, Character> characters;

		inline static std::unique_ptr<Shader> text_shader;
		inline static std::unique_ptr<VertexArray> text_vertex_array;
		inline static std::shared_ptr<VertexBuffer> text_vb;
	};
}
