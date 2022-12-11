#pragma once

#include "graphics/camera.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/particles/particles.hpp"
#include "graphics/vertex_array.hpp"
#include "physics/physics_space.hpp"
#include "audio/sound.hpp"
#include "events/event_controller.hpp"
#include "graphics/lighting/lighting.hpp"
#include "physics/physics_object.hpp"

namespace Pear
{
	class Commands
	{
	public:
		static void Start();
		static void End();

		static void StartScene(Camera& camera, float new_time_step);
		static void EndScene();

		static bool SetViewportCallback(EventData data);

		static void SetClearColor(glm::vec4 color);

		static void DrawParticle(const ParticleInfo& particle_info);
		static void DrawLightSource(const glm::vec2& pos, float size, const glm::vec3& color);

		static void DrawRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

		static void DrawRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float rotation);
		static void DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation);

		static void DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture>& texture,
			float rotation = 0.0f, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

		static void DrawShadowRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation);
		static void DrawShadowRectangle(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float rotation);

		static std::shared_ptr<CollisionObject> CreatePhysicsRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color,
			const glm::vec2& force, float restitution = 0.5f, float slow_down_factor = 1.0f, bool has_shadow = true, bool is_kinematic = true);
		static std::shared_ptr<CollisionObject> CreatePhysicsRectangle(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture>& texture,
			const glm::vec2& force, float restitution = 0.5f, float slow_down_factor = 1.0f, bool has_shadow = true, bool is_kinematic = true);

		static std::unique_ptr<Sound> LoadSoundFromFile(const std::string& path);
		static std::shared_ptr<Texture> LoadTextureFromFile(const std::string& path);

		template <typename I, typename F>
		static bool SubscribeToEvent(const EventType type, I* instance, const F& callback, const std::string& name)
		{
			return EventController::SubscribeToEvent(type, instance, callback, name);
		}
		static bool SubscribeToEvent(EventType type, const Event::Func& callback, const std::string& name);
		static bool UnsubscribeFromEvent(EventType type, const std::string& name);
		static bool FireEvent(EventType type, EventData data);

		static void MakeWindowFullscreen(bool fullscreen);
		static bool IsWindowFullscreen();
		static void ChangeWindowSize(int width, int height);
		static void SetWindowName(const std::string& new_name);

		static void DrawWireFrames(bool draw);
	private:
		static void StartGraphics();
		static void StartPhysics();
		static void StartParticles();
	private:
		inline static std::unique_ptr<Shader> shader{};
		inline static std::unique_ptr<Texture> empty_texture{};
		inline static std::unique_ptr<VertexArray> vertex_array{};

		inline static std::vector<std::shared_ptr<PhysicsObject>> physics_objects{};
		inline static std::unique_ptr<PhysicsSpace> physics_space{};

		inline static std::unique_ptr<Lighting> lighting{};

		inline static float time_step{};
	};
}
