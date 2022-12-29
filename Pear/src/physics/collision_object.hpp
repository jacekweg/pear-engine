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
		typedef std::function<void(const std::shared_ptr<CollisionObject>& this_object,
			const std::shared_ptr<CollisionObject>& second_object)> CollisionFunc;

		[[nodiscard]] bool GetIsTrigger() const;
		void SetIsTrigger(bool new_is_trigger);

		[[nodiscard]] bool GetIsStatic() const;
		void SetIsStatic(bool new_is_static);

		[[nodiscard]] bool GetIsControllable() const { return this->is_controllable; }
		void SetIsControllable(bool controllable);

		[[nodiscard]] Transform GetTransform() const;
		void SetTransform(const Transform& new_transform);

		[[nodiscard]] CollisionFunc GetOnCollisionCallback();
		void SetOnCollisionCallback(const CollisionFunc& new_callback);

		void CollisionCallback(const std::shared_ptr<CollisionObject>& this_object,
			const std::shared_ptr<CollisionObject>& second_object) const;

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

		[[nodiscard]] float GetRotation() const;
		void SetRotation(float new_rotation);

		void UpdatePosition(float time_step);

		void SwapSize();

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
		bool is_controllable{};

		Transform transform{};
		glm::vec2 prev_pos{};
		CollisionPoints collision_info{};

		bool move_up{}, move_down{}, move_left{}, move_right{};

		std::string name;

		CollisionFunc collision_callback;
	};
}
