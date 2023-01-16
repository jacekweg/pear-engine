#pragma once
#include "graphics/shader.hpp"
#include "graphics/vertex_array.hpp"

namespace Pear
{
	/**
	 * @class Lighting
	 * @brief The Lighting class for handling lighting in the Pear engine.
	 */
	class Lighting
	{
	public:
		/**
		 * @brief Initializes the Lighting subsystem.
		 */
		static void Start();

		/**
		 * @brief Adds a light source with the specified position, size and color.
		 * @param pos The position of the light source.
		 * @param size The size of the light source.
		 * @param color The color of the light source.
		 */
		static void AddLightSource(const glm::vec2& pos, float size, const glm::vec3& color);

		/**
		 * @brief Removes a light source with the specified position, size and color.
		 * @param pos The position of the light source.
		 * @param size The size of the light source.
		 * @param color The color of the light source.
		 */
		static void RemoveLightSource(const glm::vec2& pos, float size, const glm::vec3& color);

		/**
		 * @brief Adds a shadow source with the specified position, size and rotation.
		 * @param pos The position of the shadow source.
		 * @param size The size of the shadow source.
		 * @param rotation The rotation of the shadow source.
		 */
		static void AddShadowSource(const glm::vec3& pos, const glm::vec2& size, float rotation);

		/**
		 * @brief Draws the lighting.
		 */
		static void DrawLighting();

		/**
		 * @brief Sets the view-projection matrix for the Lighting subsystem.
		 * @param mat The view-projection matrix.
		 */
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
