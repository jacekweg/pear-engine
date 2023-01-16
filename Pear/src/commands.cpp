#include "pch.hpp"
#include "utils/logging.hpp"

#include "commands.hpp"
#include "physics/rectangle.hpp"
#include "graphics/text/text.hpp"
#include "graphics/vertex_buffer.hpp"
#include "events/event_controller.hpp"
#include "audio/audio.hpp"

#include <glad/glad.h>

#include "utils/random.hpp"

namespace Pear
{
	void Commands::Start()
	{
		StartGraphics();
		StartParticles();
		StartPhysics();
		Lighting::Start();
		Text::Start();
	}

	void Commands::End()
	{
		EventController::UnsubscribeFromEvent(EventType::WindowResized, "ViewportCallback");
	}

	void Commands::StartFrame(Camera& camera, const float new_time_step)
	{
		shader->Bind();
		shader->SetUniformMat4(camera.GetViewProjectionMatrix(), "view_projection");

		Lighting::SetViewProjection(camera.GetViewProjectionMatrix());

		camera.SetTimeStep(new_time_step);
		camera.OnUpdate();

		time_step = new_time_step;
	}

	void Commands::EndFrame()
	{
		Particles::OnUpdate(time_step);

		if (should_update_physics)
		{
			physics_space->OnUpdate(time_step);
			for (const auto& object : physics_objects)
			{
				object->OnUpdate(time_step);
			}
		}
		Lighting::DrawLighting();

		for (const auto& text_func : text_func_queue)
		{
			text_func();
		}
		text_func_queue.clear();
	}

	void Commands::SetClearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Commands::SetViewportCallback(const EventData data)
	{
		const int new_width = data.i32[0];
		const int new_height = data.i32[1];
		glViewport(0, 0, new_width, new_height);
		return true;
	}

	void Commands::DrawParticle(const ParticleInfo& particle_info)
	{
		Particles::Create(particle_info);
	}

	void Commands::DrawLightSource(const glm::vec2& pos, const float size, const glm::vec3& color)
	{
		Lighting::AddLightSource(pos, size, color);
	}

	void Commands::DrawRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawRectangle({ pos.x, pos.y, 0.0f }, size, color);
	}

	void Commands::DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		shader->Bind();

		shader->SetUniformFloat4(color, "square_color");
		shader->SetUniformFloat(1.0f, "tiling_factor");
		empty_texture->Bind(0);

		const auto transform = translate(glm::mat4(1.0f), pos)
			* scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		shader->SetUniformMat4(transform, "transform");
		vertex_array->Bind();

		glDrawElements(GL_TRIANGLES, static_cast<GLint>(vertex_array->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Commands::DrawRectangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const float rotation)
	{
		DrawRectangle({ pos.x, pos.y, 0.0f }, size, color, rotation);
	}

	void Commands::DrawRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const float rotation)
	{
		shader->Bind();

		shader->SetUniformFloat4(color, "square_color");
		empty_texture->Bind(0);

		const auto transform = translate(glm::mat4(1.0f), pos)
			* rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		shader->SetUniformMat4(transform, "transform");
		vertex_array->Bind();

		glDrawElements(GL_TRIANGLES, static_cast<GLint>(vertex_array->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Commands::DrawShadowRectangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const float rotation)
	{
		DrawRectangle(pos, size, color, rotation);
		Lighting::AddShadowSource(pos, size, rotation);
	}

	void Commands::DrawShadowRectangle(const glm::vec3& pos, const glm::vec2& size,
		const std::shared_ptr<Texture>& texture, const float rotation)
	{
		DrawRectangle({ pos, size, texture, rotation });
		Lighting::AddShadowSource(pos, size, rotation);
	}

	void Commands::DrawRectangle(const TextureInfo& texture_info)
	{
		const auto& [pos, size, texture, rotation, tiling_factor, tint_color] = texture_info;
		shader->Bind();

		shader->SetUniformFloat4(tint_color, "square_color");
		shader->SetUniformFloat(tiling_factor, "tiling_factor");
		texture->Bind(0);

		const auto transform = translate(glm::mat4(1.0f), pos)
			* rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		shader->SetUniformMat4(transform, "transform");

		vertex_array->Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLint>(vertex_array->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	std::shared_ptr<CollisionObject> Commands::CreatePhysicsObject(const PhysicsTextureInfo& physics_info)
	{
		const auto& [pos, size, texture, force, restitution, slow_down_factor, has_shadow, is_kinematic] = physics_info;
		const auto box = std::dynamic_pointer_cast<PhysicsObject>(std::make_shared<Rectangle>(pos, size, texture, has_shadow));
		return SetPhysicsAttributes(box, force, restitution, slow_down_factor, is_kinematic);
	}

	std::shared_ptr<CollisionObject> Commands::CreatePhysicsObject(const PhysicsColorInfo& physics_info)
	{
		const auto& [pos, size, color, force, restitution, slow_down_factor, has_shadow, is_kinematic] = physics_info;
		const auto box = std::dynamic_pointer_cast<PhysicsObject>(std::make_shared<Rectangle>(pos, size, color, has_shadow));
		return SetPhysicsAttributes(box, force, restitution, slow_down_factor, is_kinematic);
	}

	void Commands::RemovePhysicsObject(const std::shared_ptr<CollisionObject>& object)
	{
		std::erase_if(physics_objects, 
    [&](const std::shared_ptr<PhysicsObject>& physics_object)
          {
              return physics_object->GetCollisionObject() == object;
          }
		);
		physics_space->RemoveCollisionObject(object);
	}

	void Commands::UpdatePhysics(const bool should_update)
	{
		should_update_physics = should_update;
	}

	std::shared_ptr<CollisionObject> Commands::CreateTrigger(const glm::vec2& pos, const glm::vec2& size,
	                                                         const glm::vec4& color, const bool has_shadow)
	{
		auto obj = CreatePhysicsObject({ pos, size, color, { 0.0f, 0.0f }, 0.0f, 1.0f, has_shadow, false });
		obj->SetIsTrigger(true);
		return obj;
	}

	std::shared_ptr<CollisionObject> Commands::CreateTrigger(const glm::vec2& pos, const glm::vec2& size,
		const std::shared_ptr<Texture>& texture, const bool has_shadow)
	{
		auto obj = CreatePhysicsObject({ pos, size, texture, { 0.0f, 0.0f }, 0.0f, 1.0f, has_shadow, false });
		obj->SetIsTrigger(true);
		return obj;
	}

	void Commands::RemoveTrigger(const std::shared_ptr<CollisionObject>& trigger)
	{
		RemovePhysicsObject(trigger);
	}

	std::shared_ptr<CollisionObject> Commands::CreatePlayer(const glm::vec2& size,
	    const glm::vec4& color, const float slow_down_factor, const bool has_shadow)
	{
		auto obj = CreatePhysicsObject({ { 0.0f, 0.0f }, size, color, { 0.0f, 0.0f }, 0.5f, slow_down_factor, has_shadow, true });
		obj->SetIsControllable(true);
		return obj;
	}

	std::shared_ptr<CollisionObject> Commands::CreatePlayer(const glm::vec2& size,
		const std::shared_ptr<Texture>& texture, const float slow_down_factor, const bool has_shadow)
	{
		auto obj = CreatePhysicsObject({ { 0.0f, 0.0f }, size, texture, { 0.0f, 0.0f }, 0.5f, slow_down_factor, has_shadow, true });
		obj->SetIsControllable(true);
		return obj;
	}

	std::unique_ptr<Sound> Commands::LoadSoundFromFile(const std::string& path)
	{
		return Audio::LoadSound(path);
	}

	std::shared_ptr<Texture> Commands::LoadTextureFromFile(const std::string& path)
	{
		return std::make_shared<Texture>(path);
	}

	void Commands::DrawText(const std::string& text, const glm::vec2& pos, const float scale, const glm::vec3& color)
	{
		auto new_text_func = [text, pos, scale, color] { return Text::Render(text, pos, scale, color); };
		text_func_queue.emplace_back(new_text_func);
	}

	bool Commands::SubscribeToEvent(const EventType type, const Event::Func& callback, const std::string& name)
	{
		return EventController::SubscribeToEvent(type, callback, name);
	}

	bool Commands::UnsubscribeFromEvent(const EventType type, const std::string& name)
	{
		return EventController::UnsubscribeFromEvent(type, name);
	}

	bool Commands::FireEvent(const EventType type, const EventData data)
	{
		return EventController::FireEvent(type, data);
	}

	void Commands::MakeWindowFullscreen(const bool fullscreen)
	{
		Controller::GetInstance().GetWindow().MakeFullscreen(fullscreen);
	}

	bool Commands::IsWindowFullscreen()
	{
		return Controller::GetInstance().GetWindow().IsFullscreen();
	}

	void Commands::ChangeWindowSize(const int width, const int height)
	{
		Controller::GetInstance().GetWindow().SetSize(width, height);
		EventController::FireEvent(EventType::WindowResized, { .i32 = {width, height} });
	}

	void Commands::SetWindowName(const std::string& new_name)
	{
		Controller::GetInstance().GetWindow().SetName(new_name);
	}

	void Commands::DrawWireFrames(const bool draw)
	{
		if (draw)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	float Commands::RandomNumber()
	{
		return Random::Generate();
	}

	float Commands::RandomNumber(const float min, const float max)
	{
		return Random::Generate(min, max);
	}

	void Commands::StartPhysics()
	{
		physics_space = std::make_unique<PhysicsSpace>();
		physics_space->AddSolver(std::make_unique<DirectionSolver>());
		physics_space->AddSolver(std::make_unique<CollisionSolver>());
	}

	void Commands::StartParticles()
	{
		Particles::Start(300);
	}

	std::shared_ptr<CollisionObject> Commands::SetPhysicsAttributes(const std::shared_ptr<PhysicsObject>& box,
	    const glm::vec2& force, const float restitution, const float slow_down_factor, const bool is_kinematic)
	{
		box->GetCollisionObject()->SetIsKinematic(is_kinematic);
		box->GetCollisionObject()->SetAcceleration(force);
		box->GetCollisionObject()->SetRestitution(restitution);
		box->SetSlowDownFactor(slow_down_factor);
		physics_objects.emplace_back(box);
		physics_space->AddCollisionObject(box->GetCollisionObject());
		return box->GetCollisionObject();
	}

	void MessageCallback(
		[[maybe_unused]] unsigned source,
		[[maybe_unused]] unsigned type,
		[[maybe_unused]] unsigned id,
		[[maybe_unused]] unsigned severity,
		[[maybe_unused]] int length,
		const char* message,
		[[maybe_unused]] const void* user_param)
	{
		LOG("OpenGL message: {}", message)
	}

	void Commands::StartGraphics()
	{
#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		LOG("Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)))
		LOG("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)))
		LOG("OpenGL version: {}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)))

			EventController::SubscribeToEvent(EventType::WindowResized, SetViewportCallback, "ViewportCallback");

		vertex_array = std::make_unique<VertexArray>();
		float square_vertices[5 * 4] =
		{
			//vertices			//texture coordinates
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		auto square_vertices_size = static_cast<uint32_t>(sizeof square_vertices);
		auto vb = std::make_shared<VertexBuffer>(square_vertices, square_vertices_size);

		vertex_array->AddVertexBuffer(vb, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		vertex_array->AddVertexBuffer(vb, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
		auto square_indices_size = static_cast<uint32_t>(sizeof square_indices / sizeof uint32_t);
		auto ib = std::make_unique<IndexBuffer>(square_indices, square_indices_size);
		vertex_array->SetIndexBuffer(ib);

		uint32_t empty_texture_data = 0xffffff;
		empty_texture = std::make_unique<Texture>(&empty_texture_data);

		shader = std::make_unique<Shader>("res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl");
		shader->Bind();
		shader->SetUniformInt(0, "texture_data");
	}

}
