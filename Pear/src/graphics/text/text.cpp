#include "pch.hpp"
#include "text.hpp"

#include "utils/logging.hpp"

#include "controller.hpp"
#include "graphics/shader.hpp"

namespace Pear
{
	void Text::Start()
	{
        text_shader = std::make_unique<Shader>("res/shaders/text_vertex.glsl", "res/shaders/text_fragment.glsl");

        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            LOG("Could not init FreeType Library")
            return;
        }

        const std::string font_name = "res/fonts/joystix_monospace.ttf";

        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face)) 
        {
            LOG("FreeType failed to load the font")
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                LOG("Failed to load a glyph")
                continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                static_cast<GLsizei>(face->glyph->bitmap.width),
                static_cast<GLsizei>(face->glyph->bitmap.rows),
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                .texture_id = texture,
                .size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                .bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                .advance = static_cast<uint32_t>(face->glyph->advance.x)
            };
            characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        text_vertex_array = std::make_unique<VertexArray>();
        auto text_vertices_size = static_cast<uint32_t>(sizeof(float) * 6 * 4);
        text_vb = std::make_shared<VertexBuffer>(text_vertices_size);
        text_vertex_array->AddVertexBuffer(text_vb, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	}

	void Text::Render(const std::string& text, const glm::vec2& pos, const float scale, const glm::vec3& color)
	{
        text_shader->Bind();

        const int width = Controller::GetInstance().GetWindow().GetWidth();
        const int height = Controller::GetInstance().GetWindow().GetHeight();

        const glm::mat4 projection = translate(glm::mat4(1.0f), { pos + 1.0f, -0.99f })
            * glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));


        text_shader->Bind();
        text_shader->SetUniformMat4(projection, "projection");
        text_shader->SetUniformFloat3(color, "text_color");

        glActiveTexture(GL_TEXTURE0);
        text_vertex_array->Bind();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float shift = pos.x;

        for (char c : text)
        {
	        const auto& [texture_id, size, bearing, advance] = characters[c];

	        const float x_pos = shift + static_cast<float>(bearing.x) * scale;
	        const float y_pos = pos.y - (static_cast<float>(size.y) - static_cast<float>(bearing.y)) * scale;

	        const float w = static_cast<float>(size.x) * scale;
	        const float h = static_cast<float>(size.y) * scale;

	        const float vertices[6][4] = {
            { x_pos,     y_pos + h,   0.0f, 0.0f },
            { x_pos,     y_pos,       0.0f, 1.0f },
            { x_pos + w, y_pos,       1.0f, 1.0f },

            { x_pos,     y_pos + h,   0.0f, 0.0f },
            { x_pos + w, y_pos,       1.0f, 1.0f },
            { x_pos + w, y_pos + h,   1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, texture_id);
            text_vb->Bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            text_vb->Unbind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            shift += static_cast<float>((advance >> 6)) * scale;
        }
        text_vertex_array->Unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
