#pragma once
#include "pch.hpp"

#include "collider.hpp"
#include "events/event.hpp"

namespace Pear
{

	class CollisionObject;

	/**
	 * @struct CollisionInfo
	 * @brief This struct holds information about the collision.
	 */
	struct CollisionInfo
	{
		glm::vec2 a, b, normal;
		float depth;
		bool has_collision;
	};

	/**
	 * @struct Collision
	 * @brief This struct represents a collision between two objects.
	 */
	struct Collision
	{
		std::shared_ptr<CollisionObject> body_a, body_b;
		CollisionInfo collision_points;
	};

	/**
	 * @class CollisionObject
	 * @brief This class holds collision object functionality.
	 */
	class CollisionObject
	{
	public:
		/**
		 * @typedef CollisionFunc
		 * @brief A type alias for collision callback function.
		 * @param this_object A shared pointer to the first collision object.
		 * @param second_object A shared pointer to the second collision object.
		 */
		typedef std::function<void(const std::shared_ptr<CollisionObject>& this_object,
			const std::shared_ptr<CollisionObject>& second_object)> CollisionFunc;

		/**
		 * @brief Get whether the object is a trigger.
		 * @return true if the object is a trigger, false otherwise.
		 */
		[[nodiscard]] bool GetIsTrigger() const;
		/**
		 * @brief Set whether the object is a trigger.
		 * @param new_is_trigger The new value for is_trigger.
		 */
		void SetIsTrigger(bool new_is_trigger);

		/**
		 * @brief Get whether the object is static.
		 * @return true if the object is static, false otherwise.
		 */
		[[nodiscard]] bool GetIsStatic() const;
		/**
		 * @brief Set whether the object is static.
		 * @param new_is_static The new value for is_static.
		 */
		void SetIsStatic(bool new_is_static);

		/**
		 * @brief Get whether the object is controllable.
		 * @return true if the object is controllable, false otherwise.
		 */
		[[nodiscard]] bool GetIsControllable() const { return this->is_controllable; }
		/**
		 * @brief Set whether the object is controllable.
		 * @param controllable The new value for is_controllable.
		 */
		void SetIsControllable(bool controllable);

		/**
		 * @brief Get the object's transform.
		 * @return The object's transform.
		 */
		[[nodiscard]] Transform GetTransform() const;
		/**
		 * @brief Set the object's transform.
		 * @param new_transform The new transform for the object.
		 */
		void SetTransform(const Transform& new_transform);

		/**
		 * @brief Get the on collision callback function.
		 * @return The on collision callback function.
		 */
		[[nodiscard]] CollisionFunc GetOnCollisionCallback();
		/**
		 * @brief Set the on collision callback function.
		 * @param new_callback The new callback function.
		 */
		void SetOnCollisionCallback(const CollisionFunc& new_callback);

		/**
		 * @brief Call the on collision callback function.
		 * @param this_object A shared pointer to the first collision object.
		 * @param second_object A shared pointer to the second collision object.
		 */
		void CollisionCallback(const std::shared_ptr<CollisionObject>& this_object,
			const std::shared_ptr<CollisionObject>& second_object) const;

		/**
		 * @brief Set the collision points of the object.
		 * @param new_collision_info The new collision points for the object.
		 */
		void SetCollisionInfo(CollisionPoints new_collision_info);
		/**
		 * @brief Get the collision points of the object.
		 * @return The object's collision points.
		 */
		[[nodiscard]] CollisionPoints GetCollisionInfo() const;

		/**
		 * @brief Get the position of the object.
		 * @return The position of the object.
		 */
		[[nodiscard]] const glm::vec2& GetPosition() const;
		/**
		 * @brief Set the position of the object.
		 * @param new_position The new position for the object.
		 */
		void SetPosition(const glm::vec2& new_position);

		/**
		 * @brief Get the force applied to the object.
		 * @return The force applied to the object.
		 */
		[[nodiscard]] const glm::vec2& GetForce() const;
		/**
		 * @brief Set the force applied to the object.
		 * @param new_force The new force for the object.
		 */
		void SetForce(const glm::vec2& new_force);
		/**
		 * @brief Add force to the object.
		 * @param new_force The force to add to the object.
		 */
		void AddForce(const glm::vec2& new_force);

		/**
		 * @brief Get the velocity of the object.
		 * @return The velocity of the object.
		 */
		[[nodiscard]] const glm::vec2& GetVelocity() const;
		/**
		 * @brief Set the velocity of the object.
		 * @param new_velocity The new velocity for the object.
		 */
		void SetVelocity(const glm::vec2& new_velocity);

		/**
		 * @brief Get the acceleration of the object.
		 * @return The acceleration of the object.
		 */
		[[nodiscard]] glm::vec2 GetAcceleration() const;
		/**
		 * @brief Set the acceleration of the object.
		 * @param new_acceleration The new acceleration for the object.
		 */
		void SetAcceleration(const glm::vec2& new_acceleration);

		/**
		 * @brief Get the restitution of the object.
		 * @return The restitution of the object.
		 */
		[[nodiscard]] float GetRestitution() const;
		/**
		 * @brief Set the restitution of the object.
		 * @param new_restitution The new restitution for the object.
		 */
		void SetRestitution(float new_restitution);

		/**
		 * @brief Get whether the object is kinematic.
		 * @return true if the object is kinematic, false otherwise.
		 */
		[[nodiscard]] bool GetIsKinematic() const;
		/**
		 * @brief Set whether the object is kinematic.
		 * @param new_is_kinematic The new value for is_kinematic.
		 */
		void SetIsKinematic(bool new_is_kinematic);

		/**
		 * @brief Get the rotation of the object.
		 * @return The rotation of the object.
		 */
		[[nodiscard]] float GetRotation() const;
		/**
		 * @brief Set the rotation of the object.
		 * @param new_rotation The new rotation for the object.
		 */
		void SetRotation(float new_rotation);

		/**
		 * @brief Update the position of the object.
		 * @param time_step The time step for the update.
		 */
		void UpdatePosition(float time_step);

		/**
		 * @brief Swap the width and height of the object.
		 */
		void SwapSize();

		/**
		 * @brief Callback function for when a key is pressed.
		 * @param data The event data for the key press event.
		 * @return true if the event was handled, false otherwise.
		 */
		bool OnKeyPressedCallback(EventData data);
		/**
		 * @brief Callback function for when a key is released.
		 * @param data The event data for the key release event.
		 * @return true if the event was handled, false otherwise.
		 */
		bool OnKeyReleasedCallback(EventData data);

		/**
		 * @brief Get the object's previous position.
		 * @return The object's previous position.
		 */
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
