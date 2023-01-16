#pragma once
#include "pch.hpp"

namespace Pear
{
	/**
	 * @struct ParticleInfo
	 * @brief The information needed to create a particle.
	 */
	struct ParticleInfo
	{
		glm::vec2 position{}, velocity{};
		glm::vec4 start_color{}, end_color{};
		glm::vec2 start_size{}, end_size{};
		float rotation = 0.0f;
		float life_time = 0.0f;
	};

	/**
	 * @class Particles
	 * @brief The Particles class for handling particles in the Pear engine.
	 */
	class Particles
	{
	public:
		/**
		 * @brief Initializes the Particles subsystem with a specified amount of particles.
		 * @param amount The amount of particles to be created.
		 */
		static void Start(uint32_t amount);

		/**
		 * @brief Updates the Particles subsystem with a specified delta time.
		 * @param delta_time The delta time for the update.
		 */
		static void OnUpdate(float delta_time);

		/**
		 * @brief Creates a new particle with the specified particle information.
		 * @param particle_info The particle information for the new particle.
		 */
		static void Create(const ParticleInfo& particle_info);
	private:

		/**
		 * @brief Respawns a particle with new particle information.
		 * @param new_particle_info The new particle information.
		 */
		static void RespawnParticle(const ParticleInfo& new_particle_info);

		/**
		 * @brief Finds and sets the next free particle slot.
		 */
		static void SetFreeParticleSlot();
	private:
		enum RotationDir { Left, Right };
		inline static std::vector<std::tuple<ParticleInfo, float, RotationDir>> particles;

		inline static uint32_t free_particle_idx = 0;
	};
}
