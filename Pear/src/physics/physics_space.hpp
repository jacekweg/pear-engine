#pragma once
#include "pch.hpp"

#include "solver.hpp"
#include "collision_object.hpp"

namespace Pear
{
	class PhysicsSpace
	{
	public:
		void AddCollisionObject(const std::shared_ptr<CollisionObject>& obj);
		void RemoveCollisionObject(const std::shared_ptr<CollisionObject>& obj);

		void AddSolver(std::unique_ptr <Solver> solver);
		void RemoveSolver(std::unique_ptr <Solver> solver);

		void SolveCollisions(std::vector<Collision>& collisions, float time_step) const;
		void SendCollisionCallbacks(std::vector<Collision>& collisions, float time_step) const;
		void SetCallbackOnCollision(const std::function<void(Collision&, float)>& new_callback);

		void ResolveCollisions(float time_step) const;

		void MoveObjects(float time_step) const;
		void OnUpdate(float time_step) const;
	private:
		std::vector<std::shared_ptr<CollisionObject>> objects;
		std::vector<std::unique_ptr<Solver>> solvers{};
		std::function<void(Collision&, float)> callback;
	};
}
