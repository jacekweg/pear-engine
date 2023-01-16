#pragma once

#include "collision_object.hpp"

namespace Pear
{
	/**
	 * @class PhysicsObject
	 * @brief An abstract class representing a physics object in the game.
	 */
	class PhysicsObject
	{
	public:
		/**
		 * @brief Constructs a new PhysicsObject.
		 */
		PhysicsObject()
			:collision_object(std::make_shared<CollisionObject>()) {}
		/**
		 * @brief Destroys the PhysicsObject.
		 */
		virtual ~PhysicsObject() = default;

		// Deleted copy and move constructors and assignment operators
		PhysicsObject(const PhysicsObject&) = delete;
		PhysicsObject& operator=(const PhysicsObject&) = delete;
		PhysicsObject(PhysicsObject&&) = delete;
		PhysicsObject& operator=(PhysicsObject&&) = delete;

		/**
		 * @brief Gets the collision object associated with the physics object.
		 * @return The collision object associated with the physics object.
		 */
		virtual std::shared_ptr<CollisionObject> GetCollisionObject() = 0;

		/**
		 * @brief Updates the physics object.
		 * @param time_step The time step for the update.
		 */
		virtual void OnUpdate(float time_step) = 0;
		/**
		 * @brief Sets the slow down factor for the physics object.
		 * @param factor The new slow down factor.
		 */
		virtual void SetSlowDownFactor(float factor) = 0;

	protected:
		std::shared_ptr<CollisionObject> collision_object;
	};
}
