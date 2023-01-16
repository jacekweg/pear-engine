#pragma once
#include "pch.hpp"

#include "collision_object.hpp"

namespace Pear
{
	/**
	 * @class Solver
	 * @brief A base abstract class for collision solvers.
	 */
	class Solver
	{
	public:
		/**
		 * @brief Constructs a new Solver object.
		 */
		Solver() = default;
		/**
		 * @brief Destroys the Solver object.
		 */
		virtual ~Solver() = default;

		// Deleted copy and move constructors and assignment operators
		Solver(const Solver&) = delete;
		Solver& operator=(const Solver&) = delete;
		Solver(Solver&&) = delete;
		Solver& operator=(Solver&&) = delete;

		/**
		 * @brief Solves the collisions.
		 * @param collisions The collisions to solve.
		 */
		virtual void Solve(std::vector<Collision>& collisions) const = 0;
	};

	/**
	 * @class DirectionSolver
	 * @brief A solver that changes the direction of the objects involved in a collision.
	 * @extends Solver
	 */
	class DirectionSolver final : public Solver
	{
	public:
		/**
		 * @brief Solves the collisions.
		 * @param collisions The collisions to solve.
		 */
		void Solve(std::vector<Collision>& collisions) const override;
	};

	/**
	 * @class CollisionSolver
	 * @brief A solvers that applies collision response to the objects involved in a collision.
	 * @extends Solver
	 */
	class CollisionSolver final : public Solver
	{
	public:
		/**
		 * @brief Solves the collisions
		 * @param collisions The collisions to solve.
		 */
		void Solve(std::vector<Collision>& collisions) const override;
	};
}
