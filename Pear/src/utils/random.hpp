#pragma once
#include "pch.hpp"

namespace Pear
{
	class Random
	{
	public:
		static void Init()
		{
			random_engine.seed(std::random_device()());
		}

		static float Generate()
		{
			/* Generate random number between 0 and 1 */
			return static_cast<float>(distribution(random_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

	private:
		inline static std::mt19937 random_engine;
		inline static std::uniform_int_distribution<std::mt19937::result_type> distribution;
	};
}
