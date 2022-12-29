#include "pch.hpp"
#include "collision_object.hpp"

#include "events/event_controller.hpp"
#include "GLFW/glfw3.h"

namespace Pear
{
	constexpr float MOVE_EPSILON = 0.001f;

	bool CollisionObject::GetIsTrigger() const
	{
		return this->is_trigger;
	}

	void CollisionObject::SetIsTrigger(const bool new_is_trigger)
	{
		this->is_trigger = new_is_trigger;
	}

	bool CollisionObject::GetIsStatic() const
	{
		return this->is_static;
	}

	void CollisionObject::SetIsStatic(const bool new_is_static)
	{
		this->is_static = new_is_static;
	}

	void CollisionObject::SetIsControllable(const bool controllable)
	{
		this->name = std::to_string(reinterpret_cast<uint64_t>(this));
		if (controllable)
		{
			EventController::SubscribeToEvent(EventType::KeyPressed, this, &CollisionObject::OnKeyPressedCallback, "ColKeyPressed" + this->name);
			EventController::SubscribeToEvent(EventType::KeyReleased, this, &CollisionObject::OnKeyReleasedCallback, "ColKeyReleased" + this->name);
		}
		else
		{
			EventController::UnsubscribeFromEvent(EventType::KeyPressed, "ColKeyPressed" + this->name);
			EventController::UnsubscribeFromEvent(EventType::KeyReleased, "ColKeyReleased" + this->name);
		}

		this->is_controllable = controllable;
	}

	Transform CollisionObject::GetTransform() const
	{
		return this->transform;
	}

	void CollisionObject::SetTransform(const Transform& new_transform)
	{
		this->transform = new_transform;
	}

	CollisionObject::CollisionFunc CollisionObject::GetOnCollisionCallback()
	{
		return this->collision_callback;
	}

	void CollisionObject::SetOnCollisionCallback(const CollisionFunc& new_callback)
	{
		this->collision_callback = new_callback;
	}

	void CollisionObject::CollisionCallback(const std::shared_ptr<CollisionObject>& this_object,
		const std::shared_ptr<CollisionObject>& second_object) const
	{
		if(this->collision_callback)
			this->collision_callback(this_object, second_object);
	}

	void CollisionObject::SetCollisionInfo(const CollisionPoints new_collision_info)
	{
		this->collision_info = new_collision_info;
	}

	CollisionPoints CollisionObject::GetCollisionInfo() const
	{
		return this->collision_info;
	}

	const glm::vec2& CollisionObject::GetPosition() const
	{
		return this->transform.position;
	}

	void CollisionObject::SetPosition(const glm::vec2& new_position)
	{
		if (length(new_position - this->transform.position) < MOVE_EPSILON && !is_controllable)
			return;
		if (this->is_kinematic)
		{
			this->prev_pos = this->transform.position;
			this->transform.position = new_position;
		}
	}

	const glm::vec2& CollisionObject::GetForce() const
	{
		return this->force;
	}

	void CollisionObject::SetForce(const glm::vec2& new_force)
	{
		this->force = new_force;
	}

	void CollisionObject::AddForce(const glm::vec2& new_force)
	{
		this->force += new_force;
	}

	const glm::vec2& CollisionObject::GetVelocity() const
	{
		return this->velocity;
	}

	void CollisionObject::SetVelocity(const glm::vec2& new_velocity)
	{
		this->velocity = new_velocity;
	}


	glm::vec2 CollisionObject::GetAcceleration() const
	{
		return this->acceleration;
	}

	void CollisionObject::SetAcceleration(const glm::vec2& new_acceleration)
	{
		this->acceleration = new_acceleration;
	}

	float CollisionObject::GetRestitution() const
	{
		return this->restitution;
	}

	void CollisionObject::SetRestitution(const float new_restitution)
	{
		this->restitution = new_restitution;
	}

	bool CollisionObject::GetIsKinematic() const
	{
		return this->is_kinematic;
	}

	void CollisionObject::SetIsKinematic(const bool new_is_kinematic)
	{
		this->is_kinematic = new_is_kinematic;
	}

	float CollisionObject::GetRotation() const
	{
		return this->transform.rotation;
	}

	void CollisionObject::SetRotation(const float new_rotation)
	{
		this->transform.rotation = new_rotation;
	}

	void CollisionObject::UpdatePosition(const float time_step)
	{
		if (this->is_kinematic)
		{
			const float added_force = 1.0f / time_step;
			if (this->move_up)
			{
				this->AddForce({ 0.0f, added_force });
			}
			if (this->move_down)
			{
				this->AddForce({ 0.0f, -added_force});
			}
			if (this->move_left)
			{
				this->AddForce({ -added_force, 0.0f });
			}
			if (this->move_right)
			{
				this->AddForce({ added_force, 0.0f });
			}
		}
	}

	void CollisionObject::SwapSize()
	{
		std::swap(this->collision_info.half_width, this->collision_info.half_height);
	}

	bool CollisionObject::OnKeyPressedCallback(const EventData data)
	{
		switch (data.i32[0])
		{
		case GLFW_KEY_W:
			this->move_up = true;
			break;
		case GLFW_KEY_S:
			this->move_down = true;
			break;
		case GLFW_KEY_A:
			this->move_left = true;
			break;
		case GLFW_KEY_D:
			this->move_right = true;
			break;
		default:
			break;
		}

		return true;
	}

	bool CollisionObject::OnKeyReleasedCallback(const EventData data)
	{
		switch (data.i32[0])
		{
		case GLFW_KEY_W:
			this->move_up = false;
			break;
		case GLFW_KEY_S:
			this->move_down = false;
			break;
		case GLFW_KEY_A:
			this->move_left = false;
			break;
		case GLFW_KEY_D:
			this->move_right = false;
			break;
		default:
			break;
		}

		return true;
	}

	glm::vec2 CollisionObject::GetPreviousPosition() const
	{
		return this->prev_pos;
	}
}
