#pragma once
#include "physics_object.hpp"

#include "graphics/texture.hpp"

namespace Pear
{
	/**
	 * @class Rectangle
	 * @brief A class representing a rectangle shape in the engine.
	 * @extends PhysicsObject
	 */
	class Rectangle final : public PhysicsObject
	{
	public:
		/**
		 * @brief Constructs a new rectangle with a color and shadow.
		 * @param position The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param color The color of the rectangle.
		 * @param shadow Whether the rectangle has a shadow or not.
		 */
		Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, bool shadow);
		/**
		 * @brief Constructs a new rectangle with a texture and shadow.
		 * @param position The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param texture The texture of the rectangle.
		 * @param shadow Whether the rectangle has a shadow or not.
		 */
		Rectangle(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, bool shadow);
		/**
		 * @brief Destroys the Rectangle object.
		 */
		~Rectangle() override = default;

		Rectangle(const Rectangle&) = delete;
		Rectangle& operator=(const Rectangle&) = delete;
		Rectangle(Rectangle&&) = delete;
		Rectangle& operator=(Rectangle&&) = delete;

		/**
		 * @brief Gets the collision object associated with the rectangle.
		 * @return The collision object.
		 */
		std::shared_ptr<CollisionObject> GetCollisionObject() override;
		/**
		 * @brief Renders rectangle using information obtained from physics space.
		 * @param time_step The time step for the update.
		 */
		void OnUpdate(float time_step) override;
		/**
		 * @brief Set the slow down factor for the rectangle.
		 * @param factor The slow down factor.
		 */
		void SetSlowDownFactor(float factor) override;

	private:
		glm::vec2 object_size;
		glm::vec4 object_color;

		bool slow_down{};
		float slow_down_factor{};
		bool has_shadow{};
		std::shared_ptr<Texture> texture{};
	};
}
