#pragma once
#include "pch.hpp"

namespace Pear
{
	/**
	 * @class Random
	 * @brief A random number generator class.
	 */
	class Random
	{
	public:
		/**
		 * @brief Initializes the random number generator.
		 */
		static void Init()
		{
			std::random_device os_seed;
			const uint_least32_t seed = os_seed();
			engine.seed(seed);
		}

		/**
		 * @brief Generates a random number between 0 and 1.
		 *
		 * @return A random number between 0 and 1.
		 */
		static float Generate()
		{
			return static_cast<float>(distribution(engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

		/**
		 * @brief Generates a random number between the given minimum and maximum values.
		 *
		 * @param min The minimum value of the generated number.
		 * @param max The maximum value of the generated number.
		 *
		 * @return A random number between the given minimum and maximum values.
		 */
		static float Generate(const float min, const float max)
		{
			return min + Generate() * (max - min);
		}

	private:
		inline static std::mt19937 engine;
		inline static std::uniform_int_distribution<uint32_t> distribution;
	};
}
