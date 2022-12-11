#pragma once
#include "pch.hpp"

namespace Pear
{
	struct ParticleInfo
	{
		glm::vec2 position{}, velocity{};
		glm::vec4 start_color{}, end_color{};
		glm::vec2 start_size{}, end_size{};
		float rotation = 0.0f;
		float life_time = 0.0f;
	};

	class Particles
	{
	public:
		static void Start(uint32_t amount);
		static void OnUpdate(float delta_time);
		static void Create(const ParticleInfo& particle_info);
	private:
		static void RespawnParticle(const ParticleInfo& new_particle_info);
		static void SetFreeParticleSlot();
	private:
		enum RotationDir { Left, Right };
		inline static std::vector<std::tuple<ParticleInfo, float, RotationDir>> particles;
		inline static uint32_t free_particle_idx = 0;
	};
}
