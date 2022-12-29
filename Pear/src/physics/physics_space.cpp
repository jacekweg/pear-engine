#include "pch.hpp"
#include "physics_space.hpp"

namespace Pear
{
	void PhysicsSpace::AddCollisionObject(const std::shared_ptr<CollisionObject>& obj)
	{
		this->objects.emplace_back(obj);
	}

	void PhysicsSpace::RemoveCollisionObject(const std::shared_ptr<CollisionObject>& obj)
	{
		if (const auto itr = std::ranges::find(this->objects, obj);
			itr != this->objects.end())
		{
			this->objects.erase(itr);
		}
	}

	void PhysicsSpace::AddSolver(std::unique_ptr<Solver> solver)
	{
		this->solvers.push_back(std::move(solver));
	}

	void PhysicsSpace::RemoveSolver(const std::unique_ptr<Solver> solver)
	{
		if (const auto itr = std::ranges::find(this->solvers, solver);
			itr != this->solvers.end())
		{
			this->solvers.erase(itr);
		}
	}

	void PhysicsSpace::SolveCollisions(std::vector<Collision>& collisions, const float time_step) const
	{
		for (const auto& solver : this->solvers)
		{
			solver->Solve(collisions);
		}
	}

	void PhysicsSpace::SendCollisionCallbacks(std::vector<Collision>& collisions, const float time_step) const
	{
		for(auto& collision : collisions)
		{
			if (this->callback)
				this->callback(collision, time_step);

			collision.body_a->CollisionCallback(collision.body_a, collision.body_b);
			collision.body_b->CollisionCallback(collision.body_b, collision.body_a);
		}
	}

	void PhysicsSpace::SetCallbackOnCollision(const std::function<void(Collision&, float)>& new_callback)
	{
		this->callback = new_callback;
	}

	void PhysicsSpace::ResolveCollisions(const float time_step) const
	{
		std::vector<Collision> collisions;
		std::vector<Collision> trigger_collisions;

		for(const auto& a : this->objects)
		{
			for (const auto& b : this->objects)
			{
				if (a == b)
					continue;

				if(a->GetIsTrigger() && b->GetIsTrigger())
				{
					continue;
				}

				if(const CollisionInfo points = Collider::TestCollision(
					b->GetCollisionInfo(),
					b->GetTransform(),
					a->GetCollisionInfo(),
					a->GetTransform()
				); points.has_collision)
				{
					if(a->GetIsTrigger() || b->GetIsTrigger())
					{
						trigger_collisions.emplace_back(a, b, points);
					}
					else
					{
						collisions.emplace_back(a, b, points);
					}
				}
			}
		}

		for (const auto& object : this->objects)
		{
			if (object->GetIsControllable())
				object->UpdatePosition(time_step);
		}

		SolveCollisions(collisions, time_step);

		SendCollisionCallbacks(collisions, time_step);
		SendCollisionCallbacks(trigger_collisions, time_step);
	}

	void PhysicsSpace::MoveObjects(const float time_step) const
	{
		for (const auto& object : this->objects)
		{
				const glm::vec2 acc = object->GetAcceleration();
				object->AddForce(acc);

				const glm::vec2 vel = object->GetVelocity() + object->GetForce() * time_step;
				object->SetVelocity(vel);

				glm::vec2 pos = object->GetPosition() + object->GetVelocity() * time_step;
				object->SetPosition(pos);

				object->SetForce({ 0.0f, 0.0f });
		}
	}

	void PhysicsSpace::OnUpdate(const float time_step) const
	{
		MoveObjects(time_step);
		ResolveCollisions(time_step);
	}
}
