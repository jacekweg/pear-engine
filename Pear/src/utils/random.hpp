#pragma once
#include "pch.hpp"

namespace Pear
{
	class Random
	{
	public:
		static void Init()
		{
			std::random_device os_seed;
			const uint_least32_t seed = os_seed();
			engine.seed(seed);
		}

		static float Generate()
		{
			/* Generate random number between 0 and 1 */
			return static_cast<float>(distribution(engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

	private:
		inline static std::mt19937 engine;
		inline static std::uniform_int_distribution<uint32_t> distribution;
	};
}
