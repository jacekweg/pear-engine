#include "pch.hpp"
#include "solver.hpp"

namespace Pear
{
    constexpr float COLLISION_EPSILON = 0.001f;

	void Solver::Solve(std::vector<Collision>& collisions) const
	{
		for (const auto& [body_a, body_b, collision_info] : collisions)
		{
            // Calculate relative velocity
            glm::vec2 relative_velocity = body_b->GetVelocity() - body_a->GetVelocity();

            // Calculate velocity along normal
            const float velocity_along_normal = dot(relative_velocity, collision_info.normal);

            // If the bodies are separating, continue to the next iteration
            if (velocity_along_normal >= 0)
                continue;

            // Calculate restitution
            const float e = std::min(body_a->GetRestitution(), body_b->GetRestitution());

            // Calculate impulse scalar
            const float j = -(1.0f + e) * velocity_along_normal;
            const glm::vec2 impulse = j * collision_info.normal;

            // Apply impulse to body A
            if (body_a->GetIsKinematic())
                body_a->SetVelocity(body_a->GetVelocity() - impulse);

            if (!body_a->GetIsKinematic() && !body_b->GetIsMovable())
                body_b->SetPosition(body_b->GetPreviousPosition());

            // Apply impulse to body B
            if (body_b->GetIsKinematic())
                body_b->SetVelocity(body_b->GetVelocity() + impulse);

            if (!body_b->GetIsKinematic() && !body_a->GetIsMovable())
                body_a->SetPosition(body_a->GetPreviousPosition());

            // Calculate the amount of penetration/separation
            const float penetration = collision_info.depth - COLLISION_EPSILON;

            // Calculate the amount of separation to be resolved
            const glm::vec2 separation = penetration * collision_info.normal;

            // Resolve penetration/separation for body A
            if (body_a->GetIsMovable())
                body_a->SetPosition(body_a->GetPosition() - separation);

            // Resolve penetration/separation for body B
            if (body_b->GetIsMovable())
                body_b->SetPosition(body_b->GetPosition() + separation);
		}
	}
}
