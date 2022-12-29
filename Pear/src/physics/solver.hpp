#pragma once
#include "pch.hpp"

#include "collision_object.hpp"

namespace Pear
{
	class Solver
	{
	public:
		Solver() = default;
		virtual ~Solver() = default;
		Solver(const Solver&) = delete;
		Solver& operator=(const Solver&) = delete;
		Solver(Solver&&) = delete;
		Solver& operator=(Solver&&) = delete;

		virtual void Solve(std::vector<Collision>& collisions) const = 0;
	};

	class CollisionSolver final : public Solver
	{
	public:
		void Solve(std::vector<Collision>& collisions) const override;
	};

	class DirectionSolver final : public Solver
	{
	public:
		void Solve(std::vector<Collision>& collisions) const override;
	};
}
