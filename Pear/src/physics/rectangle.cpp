#include "pch.hpp"
#include "rectangle.hpp"

#include "commands.hpp"

namespace Pear
{
	Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const bool shadow)
		:object_size(size), object_color(color), has_shadow(shadow)
	{
		const glm::vec2 half_size = size / 2.0f;
		CollisionPoints collider;
		collider.half_width = half_size.x;
		collider.half_height = half_size.y;

		this->collision_object->SetTransform({ position, {1.0f, 1.0f} });
		this->collision_object->SetCollisionInfo(collider);
	}

	Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, const bool shadow)
		:Rectangle(position, size, { 0.0f, 0.0f, 0.0f, 1.0f}, shadow)
	{
		this->texture = texture;
	}

	std::shared_ptr<CollisionObject> Rectangle::GetCollisionObject()
	{
		return this->collision_object;
	}

	void Rectangle::OnUpdate(const float time_step)
	{
		const auto position = this->collision_object->GetTransform().position;
		const auto rotation = this->collision_object->GetRotation();
		const auto size = this->object_size;
		const auto color = this->object_color;
		if (this->has_shadow && this->texture)
		{
			Commands::DrawShadowRectangle({ position, 0.0f }, size, this->texture, rotation);
		}
		else if (this->has_shadow && !this->texture)
		{
			Commands::DrawShadowRectangle({ position, 0.0f }, size, color, rotation);
		}
		else if (!this->has_shadow && this->texture)
		{
			Commands::DrawRectangle({ { position, 0.0f }, size, this->texture, rotation });
		}
		else if (!this->has_shadow && !this->texture)
		{
			Commands::DrawRectangle(glm::vec3{ position, 0.0f }, size, color, rotation);
		}

		if (this->slow_down && this->slow_down_factor < 1.0f)
		{
			this->collision_object->SetVelocity(this->collision_object->GetVelocity() * (1.0f - time_step) * this->slow_down_factor);
		}
	}

	void Rectangle::SetSlowDownFactor(const float factor)
	{
		this->slow_down = true;
		this->slow_down_factor = factor;
	}
}
