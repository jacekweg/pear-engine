#pragma once
#include "pch.hpp"

namespace Pear
{
	struct CollisionInfo;

	/**
	 * @struct CollisionPoints
	 * @brief This struct holds information about collision points.
	 */
	struct CollisionPoints
	{
		glm::vec2 center{};
		float half_width{}, half_height{};
	};

	/**
	 * @struct Transform
	 * @brief This struct holds information about the position, scale, and rotation of an object.
	 */
	struct Transform
	{
		glm::vec2 position{}, scale{};
		float rotation{};
	};

	/**
	 * @class Collider
	 * @brief This class holds collision detection functionality.
	 */
	class Collider
	{
	public:
		/**
		 * @brief Test collision between two objects.
		 * @param a_collider The collision points of the first object.
		 * @param a_transform The transform of the first object.
		 * @param b_collider The collision points of the second object.
		 * @param b_transform The transform of the second object.
		 * @return CollisionInfo struct holding information about the collision.
		 */
		static CollisionInfo TestCollision(
			const CollisionPoints& a_collider,
			const Transform& a_transform,
			const CollisionPoints& b_collider,
			const Transform& b_transform
		);
	};
}
