#include "pch.hpp"
#include "collider.hpp"
#include "collision_object.hpp"

namespace Pear
{
	CollisionInfo Collider::TestCollision(
		const CollisionPoints& a_collider,
		const Transform& a_transform,
	    const CollisionPoints& b_collider,
		const Transform& b_transform)
	{
		// Transform collider centers
		const glm::vec2 transformed_center_a = a_transform.position + a_collider.center;
		const glm::vec2 transformed_center_b = b_transform.position + b_collider.center;

		// Calculate scaled collider dimensions
		const float a_scaled_width = a_collider.half_width * a_transform.scale.x;
		const float a_scaled_height = a_collider.half_height * a_transform.scale.y;
		const float b_scaled_width = b_collider.half_width * b_transform.scale.x;
		const float b_scaled_height = b_collider.half_height * b_transform.scale.y;

		// Check for overlap in x and y dimensions
		const glm::vec2 a_to_b = transformed_center_b - transformed_center_a;
		const float x_overlap = a_scaled_width + b_scaled_width - glm::abs(a_to_b.x);
		const float y_overlap = a_scaled_height + b_scaled_height - glm::abs(a_to_b.y);

		if (x_overlap <= 0.0f || y_overlap <= 0.0f)
			return {};

		// Calculate collision normal and overlap
		glm::vec2 normal;
		float overlap;
		if (x_overlap > y_overlap)
		{
			normal = (a_to_b.y > 0.0f) ? glm::vec2(0.0f, -1.0f) : glm::vec2(0.0f, 1.0f);
			overlap = y_overlap;
		}
		else
		{
			normal = (a_to_b.x > 0.0f) ? glm::vec2(-1.0f, 0.0f) : glm::vec2(1.0f, 0.0f);
			overlap = x_overlap;
		}

		// Return collision information
		return { transformed_center_a, transformed_center_b, normal, overlap, true };

	}


}
