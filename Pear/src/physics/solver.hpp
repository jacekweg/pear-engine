#pragma once
#include "pch.hpp"

#include "collision_object.hpp"

namespace Pear
{
	class Solver
	{
	public:
		void Solve(std::vector<Collision>& collisions) const;
	};
}
