#include "pch.hpp"
#include "lighting.hpp"

#include "commands.hpp"

#include <glad/glad.h>

namespace Pear
{
	void Lighting::Start()
	{
		lights.resize(10);
		shadows.resize(10);

		shadow_shader = std::make_unique<Shader>("res/shaders/shadow_vertex.glsl", "res/shaders/shadow_fragment.glsl");
		shadow_vertex_array = std::make_unique<VertexArray>();
		float shadow_vertices[6 * 5] =
		{
			-0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 1.0f,
			 0.5f,  0.5f, 0.0f,  0.5f,  0.5f, 1.0f,
			-0.5f,  0.5f, 0.0f, -0.5f,  0.5f, 1.0f,
			-0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 1.0f
		};
		auto shadow_vertices_size = static_cast<uint32_t>(sizeof shadow_vertices);
		auto shadow_vb = std::make_shared<VertexBuffer>(shadow_vertices, shadow_vertices_size);
		shadow_vertex_array->AddVertexBuffer(shadow_vb, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		light_shader = std::make_unique<Shader>("res/shaders/light_vertex.glsl", "res/shaders/light_fragment.glsl");
		light_vertex_array = std::make_unique<VertexArray>();
		float light_sprite_vertices[4 * 4] =
		{
			 10.0f,  10.0f,  10.0f,  10.0f,
			-10.0f,  10.0f, -10.0f,  10.0f,
			 10.0f, -10.0f,  10.0f, -10.0f,
			-10.0f, -10.0f, -10.0f, -10.0f
		};
		auto light_vertices_size = static_cast<uint32_t>(sizeof light_sprite_vertices);
		auto light_vb = std::make_shared<VertexBuffer>(light_sprite_vertices, light_vertices_size);

		light_vertex_array->AddVertexBuffer(light_vb, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		light_vertex_array->AddVertexBuffer(light_vb, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	}

	void Lighting::AddLightSource(const glm::vec2& pos, float size, const glm::vec3& color)
	{
		lights.emplace_back(pos, size, color);
	}

	void Lighting::RemoveLightSource(const glm::vec2& pos, float size, const glm::vec3& color)
	{
		if (const auto itr = std::ranges::find(lights, std::tuple{ pos, size, color });
			itr != lights.end())
		{
			lights.erase(itr);
		}
	}

	void Lighting::AddShadowSource(const glm::vec3& pos, const glm::vec2& size, float rotation)
	{
		shadows.emplace_back(pos, size, rotation);
	}

	void Lighting::SetViewProjection(const glm::mat4 mat)
	{
		view_projection = mat;
	}

	void Lighting::DrawLighting()
	{
		glDisable(GL_DEPTH_TEST);
		for (const auto& [pos, size, color] : lights)
		{
			for (const auto& [shadow_pos, shadow_size, shadow_rotation] : shadows)
			{
				/* draw shadows */
				const auto transform = translate(glm::mat4(1.0f), shadow_pos)
					* rotate(glm::mat4(1.0f), shadow_rotation, { 0.0f, 0.0f, 1.0f })
					* scale(glm::mat4(1.0f), { shadow_size.x, shadow_size.y, 1.0f });

				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ZERO, GL_ZERO);
				shadow_shader->Bind();
				shadow_shader->SetUniformMat4(transform, "transform");
				shadow_shader->SetUniformMat4(view_projection, "view_projection");
				shadow_shader->SetUniformFloat2(pos, "input_light_position");
				shadow_vertex_array->Bind();
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);
			}

			/* draw lights */
			const auto transform_light =
				translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
				* scale(glm::mat4(1.0f), { size, size, 1.0f });

			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE, GL_ONE, GL_ZERO);

			light_shader->Bind();
			light_shader->SetUniformFloat3(color, "input_color");
			light_shader->SetUniformMat4(transform_light, "transform");
			light_shader->SetUniformMat4(view_projection, "view_projection");
			light_vertex_array->Bind();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		shadows.clear();
		lights.clear();
	}

	void Lighting::DrawLights()
	{
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE, GL_ONE, GL_DST_ALPHA);
		glClear(GL_DEPTH_BUFFER_BIT);

		for (const auto& [pos, size, color] : lights)
		{
			/* draw lights */
			const auto transform_light =
				translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f})
				* scale(glm::mat4(1.0f), { size, size, 1.0f });

			light_shader->Bind();
			light_shader->SetUniformFloat3(color, "u_color");
			light_shader->SetUniformMat4(transform_light, "u_matrix");
			light_shader->SetUniformMat4(view_projection, "u_projection");
			light_vertex_array->Bind();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glClear(GL_DEPTH_BUFFER_BIT);

		}
	}
}
