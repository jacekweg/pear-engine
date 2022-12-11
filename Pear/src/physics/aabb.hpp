#pragma once
#include "physics_object.hpp"

#include "graphics/texture.hpp"

namespace Pear
{
	class AABB final : public PhysicsObject
	{
	public:
		AABB(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, bool shadow);
		AABB(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, bool shadow);
		~AABB() override;

		AABB(const AABB&) = delete;
		AABB& operator=(const AABB&) = delete;
		AABB(AABB&&) = delete;
		AABB& operator=(AABB&&) = delete;

		std::shared_ptr<CollisionObject> GetCollisionObject() override;
		void OnUpdate(float time_step) override;

		void SetSlowDownFactor(float factor) override;

	private:
		glm::vec2 object_size;
		glm::vec4 object_color;

		bool slow_down{};
		float slow_down_factor{};
		bool has_shadow{};
		std::shared_ptr<Texture> texture{};
	};
}
