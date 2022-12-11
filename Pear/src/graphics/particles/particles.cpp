#include "pch.hpp"
#include "particles.hpp"

#include "utils/random.hpp"
#include "commands.hpp"

namespace Pear
{
	void Particles::Start(const uint32_t amount)
	{
		particles.resize(amount);
	}

	void Particles::OnUpdate(const float delta_time)
	{
		for(auto& [particle_info, life_time_left, rotation_dir] : particles)
		{
			if(life_time_left > 0.0f)
			{
				const float current_lifetime = life_time_left / particle_info.life_time;

				particle_info.position += particle_info.velocity * delta_time;

				if(rotation_dir == Left)
					particle_info.rotation += Random::Generate() * 1.5f * delta_time;
				else
					particle_info.rotation -= Random::Generate() * 1.5f * delta_time;

				glm::vec4 new_color = lerp(particle_info.end_color, particle_info.start_color, current_lifetime);
				glm::vec2 new_size = lerp(particle_info.end_size, particle_info.start_size, current_lifetime);

				Commands::DrawRectangle(particle_info.position, new_size, new_color, particle_info.rotation);

				life_time_left -= delta_time;
			}
		}
	}

	void Particles::Create(const ParticleInfo& particle_info)
	{
		RespawnParticle(particle_info);
	}

	void Particles::RespawnParticle(const ParticleInfo& new_particle_info)
	{
		SetFreeParticleSlot();

		auto& [particle_info, life_time_left, rotation_dir] = particles[free_particle_idx];

		particle_info.position = new_particle_info.position;

		particle_info.velocity = new_particle_info.velocity;
		particle_info.velocity.x += (Random::Generate() - 0.5f) * 0.25f;
		particle_info.velocity.y += (Random::Generate() - 0.5f) * 0.25f;

		particle_info.start_color = new_particle_info.start_color;
		particle_info.start_color.r += (Random::Generate() - 0.5f) * 0.05f;
		particle_info.start_color.g += (Random::Generate() - 0.5f) * 0.05f;
		particle_info.start_color.b += (Random::Generate() - 0.5f) * 0.05f;

		particle_info.end_color = new_particle_info.end_color;
		particle_info.end_color.r += (Random::Generate() - 0.5f) * 0.05f;
		particle_info.end_color.g += (Random::Generate() - 0.5f) * 0.05f;
		particle_info.end_color.b += (Random::Generate() - 0.5f) * 0.05f;

		particle_info.start_size = new_particle_info.start_size;
		particle_info.end_size = new_particle_info.end_size;

		if (Random::Generate() > 0.5f)
			rotation_dir = Left;
		else
			rotation_dir = Right;

		particle_info.life_time = new_particle_info.life_time;
		life_time_left = new_particle_info.life_time;
	}

	void Particles::SetFreeParticleSlot()
	{
		for (uint32_t i = free_particle_idx; i < particles.size(); ++i) 
		{
			if (auto& [info, life_time_left, dir] = particles[i]; 
				life_time_left <= 0.0f)
			{
				free_particle_idx = i;
				return;
			}
		}

		for (uint32_t i = 0; i < free_particle_idx; ++i) 
		{
			if (auto& [info, life_time_left, dir] = particles[i]; 
				life_time_left <= 0.0f)
			{
				free_particle_idx = i;
				return;
			}
		}

		free_particle_idx = 0;
	}
}
