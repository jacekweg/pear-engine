#pragma once
#include "pch.hpp"

#include "solver.hpp"
#include "collision_object.hpp"

namespace Pear
{
	/**
	 * @class PhysicsSpace
	 * @brief A class representing the physics space in the game.
	 */
	class PhysicsSpace
	{
	public:
		/**
		 * @brief Adds a collision object to the physics space.
		 * @param obj The collision object to add.
		 */
		void AddCollisionObject(const std::shared_ptr<CollisionObject>& obj);
		/**
		 * @brief Removes a collision object from the physics space.
		 * @param obj The collision object to remove.
		 */
		void RemoveCollisionObject(const std::shared_ptr<CollisionObject>& obj);

		/**
		 * @brief Adds a solver to the physics space.
		 * @param solver The solver to add.
		 */
		void AddSolver(std::unique_ptr <Solver> solver);
		/**
		 * @brief Removes a solver from the physics space.
		 * @param solver The solver to remove.
		 */
		void RemoveSolver(std::unique_ptr <Solver> solver);

		/**
		 * @brief Solves the collisions in the physics space.
		 * @param collisions The vector to store the collisions.
		 * @param time_step The time step for the collision solving.
		 */
		void SolveCollisions(std::vector<Collision>& collisions, float time_step) const;
		/**
		 * @brief Sends collision callbacks for the collisions in the physics space.
		 * @param collisions The vector of collisions.
		 * @param time_step The time step for the callbacks.
		 */
		void SendCollisionCallbacks(std::vector<Collision>& collisions, float time_step) const;
		/**
		 * @brief Sets the callback function for when a collision occurs.
		 * @param new_callback The new callback function.
		 */
		void SetCallbackOnCollision(const std::function<void(Collision&, float)>& new_callback);

		/**
		 * @brief Resolves the collisions in the physics space.
		 * @param time_step The time step for the collision resolving.
		 */
		void ResolveCollisions(float time_step) const;

		/**
		 * @brief Moves the objects in the physics space.
		 * @param time_step The time step for the movement.
		 */
		void MoveObjects(float time_step) const;
		/**
		 * @brief Updates the physics space.
		 * @@param time_step The time step for the update.
		 */
		void OnUpdate(float time_step) const;
	private:
		std::vector<std::shared_ptr<CollisionObject>> objects;
		std::vector<std::unique_ptr<Solver>> solvers{};
		std::function<void(Collision&, float)> callback;
	};
}
