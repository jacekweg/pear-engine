#pragma once
#include "pch.hpp"

namespace Pear
{
	struct CollisionInfo;

	struct CollisionPoints
	{
		glm::vec2 center{};
		float half_width{}, half_height{};
	};

	struct Transform
	{
		glm::vec2 position, scale;
	};

	class Collider
	{
	public:
		static CollisionInfo TestCollision(
			const CollisionPoints& a_collider,
			const Transform& a_transform,
			const CollisionPoints& b_collider,
			const Transform& b_transform
		);
	};
}
