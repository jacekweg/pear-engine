#pragma once
#include "graphics/shader.hpp"
#include "graphics/vertex_array.hpp"

namespace Pear
{
	class Lighting
	{
	public:
		static void Start();

		static void AddLightSource(const glm::vec2& pos, float size, const glm::vec3& color);
		static void RemoveLightSource(const glm::vec2& pos, float size, const glm::vec3& color);

		static void AddShadowSource(const glm::vec3& pos, const glm::vec2& size, float rotation);

		static void DrawLighting();

		static void SetViewProjection(glm::mat4 mat);
	private:
		inline static glm::mat4 view_projection{};

		inline static std::unique_ptr<Shader> light_shader{};
		inline static std::unique_ptr<Shader> shadow_shader{};

		inline static std::unique_ptr<VertexArray> shadow_vertex_array{};
		inline static std::unique_ptr<VertexArray> light_vertex_array{};

		inline static std::vector<std::tuple<glm::vec3, glm::vec2, float>> shadows{};
		inline static std::vector<std::tuple<glm::vec2, float, glm::vec3>> lights{};
	};
}
