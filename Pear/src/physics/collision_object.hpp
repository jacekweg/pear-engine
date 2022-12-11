#pragma once
#include "pch.hpp"

#include "collider.hpp"
#include "events/event.hpp"

namespace Pear
{
	class CollisionObject;

	struct CollisionInfo
	{
		glm::vec2 a, b, normal;
		float depth;
		bool has_collision;
	};

	struct Collision
	{
		std::shared_ptr<CollisionObject> body_a, body_b;
		CollisionInfo collision_points;
	};

	class CollisionObject
	{
	public:
		[[nodiscard]] bool GetIsTrigger() const;
		void SetIsTrigger(bool new_is_trigger);

		[[nodiscard]] bool GetIsStatic() const;
		void SetIsStatic(bool new_is_static);

		[[nodiscard]] bool GetIsMovable() const { return this->is_movable; }
		void SetIsMovable(bool movable);

		[[nodiscard]] Transform GetTransform() const;
		void SetTransform(const Transform& new_transform);

		[[nodiscard]] std::function<void(const std::shared_ptr<CollisionObject>& collision_object)> GetOnCollisionCallback();
		void SetOnCollisionCallback(const std::function<void(const std::shared_ptr<CollisionObject>& collision_object)>& new_callback);

		void CollisionCallback(const std::shared_ptr<CollisionObject>& collision_object) const;

		void SetCollisionInfo(CollisionPoints new_collision_info);
		[[nodiscard]] CollisionPoints GetCollisionInfo() const;

		[[nodiscard]] const glm::vec2& GetPosition() const;
		void SetPosition(const glm::vec2& new_position);

		[[nodiscard]] const glm::vec2& GetForce() const;
		void SetForce(const glm::vec2& new_force);
		void AddForce(const glm::vec2& new_force);

		[[nodiscard]] const glm::vec2& GetVelocity() const;
		void SetVelocity(const glm::vec2& new_velocity);

		[[nodiscard]] glm::vec2 GetAcceleration() const;
		void SetAcceleration(const glm::vec2& new_acceleration);

		[[nodiscard]] float GetRestitution() const;
		void SetRestitution(float new_restitution);

		[[nodiscard]] bool GetIsKinematic() const;
		void SetIsKinematic(bool new_is_kinematic);

		void UpdatePosition(float time_step);

		bool OnKeyPressedCallback(EventData data);
		bool OnKeyReleasedCallback(EventData data);

		[[nodiscard]] glm::vec2 GetPreviousPosition() const;

	private:
		glm::vec2 force{};
		glm::vec2 velocity{};
		glm::vec2 acceleration{};

		float restitution{};

		bool is_static{};
		bool is_trigger{};
		bool is_kinematic{};
		bool is_movable{};

		Transform transform{};
		glm::vec2 prev_pos{};
		CollisionPoints collision_info{};

		bool move_up{}, move_down{}, move_left{}, move_right{};
		float transform_speed = 2.0f;

		std::string name;

		std::function<void(const std::shared_ptr<CollisionObject>& collision_object)> collision_callback;
	};
}
