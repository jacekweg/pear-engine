#pragma once

#include "collision_object.hpp"

namespace Pear
{
	class PhysicsObject
	{
	public:
		PhysicsObject():collision_object(std::make_shared<CollisionObject>()){}
		virtual ~PhysicsObject() = default;

		PhysicsObject(const PhysicsObject&) = delete;
		PhysicsObject& operator=(const PhysicsObject&) = delete;
		PhysicsObject(PhysicsObject&&) = delete;
		PhysicsObject& operator=(PhysicsObject&&) = delete;

		virtual std::shared_ptr<CollisionObject> GetCollisionObject() = 0;
		virtual void OnUpdate(float time_step) = 0;
		virtual void SetSlowDownFactor(float factor) = 0;

	protected:
		std::shared_ptr<CollisionObject> collision_object;
	};
}
