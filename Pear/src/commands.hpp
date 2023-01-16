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
	/**
	 * @struct TextureInfo
	 *
	 * @brief Structure containing information for drawing a textured rectangle.
	 *
	 * @var TextureInfo::pos
	 * The position of the rectangle.
	 *
	 * @var TextureInfo::size
	 * The size of the rectangle.
	 *
	 * @var TextureInfo::texture
	 * The texture to be applied to the rectangle.
	 *
	 * @var TextureInfo::rotation
	 * The rotation of the rectangle, in degrees.
	 *
	 * @var TextureInfo::tiling_factor
	 * The tiling factor of the rectangle's texture.
	 *
	 * @var TextureInfo::tint_color
	 * The tint color of the rectangle.
	 */
	struct TextureInfo
	{
		const glm::vec3& pos;
		const glm::vec2& size;
		const std::shared_ptr<Texture>& texture;
		float rotation = 0.0f;
		float tiling_factor = 1.0f;
		const glm::vec4& tint_color = glm::vec4(1.0f);
	};

	/**
	 * @struct PhysicsTextureInfo
	 *
	 * @brief Structure containing information for creating a textured physics object.
	 *
	 * @var PhysicsTextureInfo::pos
	 * The position of the object.
	 *
	 * @var PhysicsTextureInfo::size
	 * The size of the object.
	 *
	 * @var PhysicsTextureInfo::texture
	 * The texture to be applied to the object.
	 *
	 * @var PhysicsTextureInfo::force
	 * The force to be applied to the object.
	 *
	 * @var PhysicsTextureInfo::restitution
	 * The restitution of the object.
	 *
	 * @var PhysicsTextureInfo::slow_down_factor
	 * The slow down factor of the object.
	 *
	 * @var PhysicsTextureInfo::has_shadow
	 * Whether the object has a shadow or not.
	 *
	 * @var PhysicsTextureInfo::is_kinematic
	 * Whether the object is kinematic or not.
	 */
	struct PhysicsTextureInfo
	{
		const glm::vec2& pos;
		const glm::vec2& size;
		const std::shared_ptr<Texture>& texture;
		const glm::vec2& force;
		float restitution = 0.5f;
		float slow_down_factor = 1.0f;
		bool has_shadow = true;
		bool is_kinematic = true;
	};
	/**
	 * @struct PhysicsColorInfo
	 *
	 * @brief Structure containing information for creating a colored physics object.
	 *
	 * @var PhysicsColorInfo::pos
	 * The position of the object.
	 *
	 * @var PhysicsColorInfo::size
	 * The size of the object.
	 *
	 * @var PhysicsColorInfo::color
	 * The color of the object.
	 *
	 * @var PhysicsColorInfo::force
     * The force to be applied to the object.
     *
     * @var PhysicsColorInfo::restitution
     * The restitution of the object.
     *
     * @var PhysicsColorInfo::slow_down_factor
     * The slow down factor of the object.
     *
     * @var PhysicsColorInfo::has_shadow
     * Whether the object has a shadow or not.
     *
     * @var PhysicsColorInfo::is_kinematic
     * Whether the object is kinematic or not.
     */
	struct PhysicsColorInfo
	{
		const glm::vec2& pos;
		const glm::vec2& size;
		const glm::vec4& color;
		const glm::vec2& force;
		float restitution = 0.5f;
		float slow_down_factor = 1.0f;
		bool has_shadow = true;
		bool is_kinematic = true;
	};

	/**
	 * @class Commands
	 *
	 * @brief A class used to communicate with the Pear engine. Provides access to all of its functionality.
	 */
	class Commands
	{
	public:
		/**
		 * @brief Starts rendering.
		 */
		static void Start();
		/**
		 * @brief Ends rendering.
		 */
		static void End();

		/**
		 * @brief Starts a new frame of rendering.
		 *
		 * @param camera The camera to be used for the frame.
		 * @param new_time_step The time step for the frame.
		 */
		static void StartFrame(Camera& camera, float new_time_step);
		/**
		 * @brief Ends the current frame of rendering.
		 */
		static void EndFrame();

		/**
		 * @brief Sets the viewport callback.
		 *
		 * @param data The event data for the viewport callback.
		 *
		 * @return Whether the viewport callback was set successfully or not.
		 */
		static bool SetViewportCallback(EventData data);

		/**
		 * @brief Sets the clear color for the screen.
		 *
		 * @param color The color to be used for clearing the screen.
		 */
		static void SetClearColor(glm::vec4 color);

		/**
		 * @brief Draws a particle on screen.
		 *
		 * @param particle_info The information about the particle to be drawn.
		 */
		static void DrawParticle(const ParticleInfo& particle_info);
		/**
		 * @brief Draws a shadow rectangle on screen.
		 *
		 * @param pos The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param color The color of the rectangle.
		 * @param rotation The rotation of the rectangle, in degrees.
		 */
		static void DrawShadowRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation);
		/**
		 * @brief Draws a shadow rectangle with a texture on screen.
         *
         * @param pos The position of the rectangle.
         * @param size The size of the rectangle.
         * @param texture The texture to be applied to the rectangle.
         * @param rotation The rotation of the rectangle, in degrees.
         */
		static void DrawShadowRectangle(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float rotation);

		/**
		 * @brief Draws a light source on screen.
		 *
		 * @param pos The position of the light source.
		 * @param size The size of the light source.
		 * @param color The color of the light source.
		 */
		static void DrawLightSource(const glm::vec2& pos, float size, const glm::vec3& color);

		/**
		 * @brief Draws a rectangle on screen.
		 *
		 * @param pos The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param color The color of the rectangle.
		 */
		static void DrawRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		/**
		 * @brief Draws a rectangle on screen.
		 *
		 * @param pos The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param color The color of the rectangle.
		 */
		static void DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

		/**
		 * @brief Draws a rectangle on screen.
		 *
		 * @param pos The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param color The color of the rectangle.
		 * @param rotation The rotation of the rectangle, in degrees.
		 */
		static void DrawRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float rotation);
		/**
		 * @brief Draws a rectangle on screen.
		 *
		 * @param pos The position of the rectangle.
		 * @param size The size of the rectangle.
		 * @param color The color of the rectangle.
		 * @param rotation The rotation of the rectangle, in degrees.
		 */
		static void DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation);

		/**
		 * @brief Draws a textured rectangle on screen.
		 *
		 * @param texture_info The information for the textured rectangle to be drawn.
		 */
		static void DrawRectangle(const TextureInfo& texture_info);

		/**
		 * @brief Creates a physics object with a texture.
		 *
		 * @param physics_info The information for the physics object to be created.
		 *
		 * @return A shared pointer to the created physics object.
		 */
		static std::shared_ptr<CollisionObject> CreatePhysicsObject(const PhysicsTextureInfo& physics_info);
		/**
		 * @brief Creates a physics object with a color.
		 *
		 * @param physics_info The information for the physics object to be created.
		 *
		 * @return A shared pointer to the created physics object.
		 */
		static std::shared_ptr<CollisionObject> CreatePhysicsObject(const PhysicsColorInfo& physics_info);
		/**
		 * @brief Removes a physics object.
		 *
		 * @param object The shared pointer to the physics object to be removed.
		 */
		static void RemovePhysicsObject(const std::shared_ptr<CollisionObject>& object);

		/**
		 * @brief Sets whether the physics space should be updated.
		 *
		 * @param should_update Whether the physics should be updated or not.
		 */
		static void UpdatePhysics(bool should_update);

		/**
		 * @brief Creates a trigger with a color.
		 *
		 * @param pos The position of the trigger.
		 * @param size The size of the trigger.
		 * @param color The color of the trigger.
		 * @param has_shadow Whether the trigger has a shadow or not.
		 *
		 * @return A shared pointer to the created trigger.
		 */
		static std::shared_ptr<CollisionObject> CreateTrigger(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, bool has_shadow = true);
		/**
		 * @brief Creates a trigger with a texture.
		 *
		 * @param pos The position of the trigger.
		 * @param size The size of the trigger.
		 * @param texture The texture of the trigger.
		 * @param has_shadow Whether the trigger has a shadow or not.
		 *
		 * @return A shared pointer to the created trigger.
		 */
		static std::shared_ptr<CollisionObject> CreateTrigger(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture>& texture, bool has_shadow = true);
		/**
		 * @brief Removes a trigger.
		 *
		 * @param trigger The shared pointer to the trigger to be removed.
		 */
		static void RemoveTrigger(const std::shared_ptr<CollisionObject>& trigger);
		/**
		 * @brief Creates a player with a color.
		 *
		 * @param size The size of the player.
		 * @param color The color of the player.
		 * @param slow_down_factor The slow down factor of the player.
         * @param has_shadow Whether the player has a shadow or not.
         *
         * @return A shared pointer to the created player.
         */
		static std::shared_ptr<CollisionObject> CreatePlayer(const glm::vec2& size, const glm::vec4& color, float slow_down_factor = 0.5f, bool has_shadow = true);
		/**
		 * @brief Creates a player with a texture.
		 *
		 * @param size The size of the player.
		 * @param texture The texture of the player.
		 * @param slow_down_factor The slow down factor of the player.
		 * @param has_shadow Whether the player has a shadow or not.
		 *
		 * @return A shared pointer to the created player.
		 */
		static std::shared_ptr<CollisionObject> CreatePlayer(const glm::vec2& size, const std::shared_ptr<Texture>& texture, float slow_down_factor = 0.5f, bool has_shadow = true);

		/**
		 * @brief Loads a sound from a file.
		 *
		 * @param path The path to the file.
		 *
		 * @return A unique pointer to the loaded sound.
		 */
		static std::unique_ptr<Sound> LoadSoundFromFile(const std::string& path);
		/**
		 * @brief Loads a texture from a file.
		 *
		 * @param path The path to the file.
		 *
		 * @return A shared pointer to the loaded texture.
		 */
		static std::shared_ptr<Texture> LoadTextureFromFile(const std::string& path);

		/**
		 * @brief Draws text on screen.
		 *
		 * @param text The text to be drawn.
		 * @param pos The position of the text.
		 * @param scale The scale of the text.
		 * @param color The color of the text.
		 */
		static void DrawText(const std::string& text, const glm::vec2& pos, float scale, const glm::vec3& color);

		/**
		 * @brief Subscribes to an event.
		 *
		 * @tparam I The type of the instance.
		 * @tparam F The type of the callback function.
		 *
		 * @param type The type of the event.
		 * @param instance The instance to be passed to the callback function.
		 * @param callback The callback function to be called when the event is fired.
		 * @param name A unique name to identify the subscriber.
		 *
		 * @return Whether the subscription was successful or not.
		 */
		template <typename I, typename F>
		static bool SubscribeToEvent(const EventType type, I* instance, const F& callback, const std::string& name)
		{
			return EventController::SubscribeToEvent(type, instance, callback, name);
		}

		/**
		 * @brief Subscribes to an event.
		 *
		 * @param type The type of the event.
		 * @param callback The callback function to be called when the event is fired.
		 * @param name A unique name to identify the subscriber.
		 *
		 * @return Whether the subscription was successful or not.
		 */
		static bool SubscribeToEvent(EventType type, const Event::Func& callback, const std::string& name);
		/**
		 * @brief Unsubscribes from an event.
		 *
		 * @param type The type of the event.
		 * @param name The name of the subscriber to be unsubscribed.
		 *
		 * @return Whether the unsubscription was successful or not.
		 */
		static bool UnsubscribeFromEvent(EventType type, const std::string& name);
		/**
		 * @brief Fires an event.
		 *
		 * @param type The type of the event.
		 * @param data The data to be passed to the subscribers.
		 *
		 * @return Whether the event was handled by all of the callback functions.
		 */
		static bool FireEvent(EventType type, EventData data);
		/**
		 * @brief Makes the window fullscreen.
		 *
		 * @param fullscreen Whether the window should be made fullscreen or not.
         */
		static void MakeWindowFullscreen(bool fullscreen);
		/**
		 * @brief Check if the window is fullscreen or not.
		 *
		 * @return Whether the window is fullscreen or not.
		 */
		static bool IsWindowFullscreen();
		/**
		 * @brief Changes the size of the window.
		 *
		 * @param width The new width of the window.
		 * @param height The new height of the window.
		 */
		static void ChangeWindowSize(int width, int height);
		/**
		 * @brief Sets the name of the window.
		 *
		 * @param new_name The new name of the window.
		 */
		static void SetWindowName(const std::string& new_name);

		/**
		 * @brief Changes whether the wireframes should be drawn instead on regular objects.
		 *
		 * @param draw Whether wireframes should be drawn or not.
		 */
		static void DrawWireFrames(bool draw);
		/**
		 * @brief Generates a random number.
		 *
		 * @return A random number between 0 and 1.
		 */
		static float RandomNumber();
		/**
		 * @brief Generates a random number.
		 *
		 * @param min The minimum value of the generated number.
		 * @param max The maximum value of the generated number.
		 *
		 * @return A random number between the given minimum and maximum values.
		 */
		static float RandomNumber(float min, float max);
	private:
		/**
		 * @brief Starts the graphics module.
		 */
		static void StartGraphics();
		/**
		 * @brief Starts the physics module.
		 */
		static void StartPhysics();
		/**
		 * @brief Starts the particles system.
		 */
		static void StartParticles();

		/**
		 * @brief Sets the physics attributes of a collision object.
		 *
		 * @param box The collision object to set the attributes to.
		 * @param force The force applied to the collision object.
		 * @param restitution The restitution of the collision object.
		 * @param slow_down_factor The slow down factor of the collision object.
		 * @param is_kinematic Whether the collision object is kinematic or not.
		 *
		 * @return A shared pointer to the updated collision object.
		 */
		static std::shared_ptr<CollisionObject> SetPhysicsAttributes(const std::shared_ptr<PhysicsObject>& box,
		    const glm::vec2& force, float restitution, float slow_down_factor, bool is_kinematic);
	private:
		inline static std::unique_ptr<Shader> shader{};
		inline static std::unique_ptr<Texture> empty_texture{};
		inline static std::unique_ptr<VertexArray> vertex_array{};

		inline static std::vector<std::shared_ptr<PhysicsObject>> physics_objects{};
		inline static std::unique_ptr<PhysicsSpace> physics_space{};

		inline static std::unique_ptr<Lighting> lighting{};
		inline static std::vector<std::function<void()>> text_func_queue{};

		inline static float time_step{};

		inline static bool should_update_physics = true;
	};
}
