#include <pear.hpp>

#include "demo.hpp"

Demo::Demo()
{
	Pear::Commands::Start();

	Pear::Commands::SetWindowName("My app");
	Pear::Commands::ChangeWindowSize(2560, 1600);

	//this->camera.SetMaxZoom(6.5f);
	this->camera.SetMinZoom(1.0f);

	this->short_sound = Pear::Commands::LoadSoundFromFile("res/audio/short.mp3");
	this->background_sound = Pear::Commands::LoadSoundFromFile("res/audio/background.mp3");

	this->player_texture = Pear::Commands::LoadTextureFromFile("res/textures/spaceship.png");
	this->asteroid_texture = Pear::Commands::LoadTextureFromFile("res/textures/asteroid.png");
	this->background_texture = Pear::Commands::LoadTextureFromFile("res/textures/background_2.png");

	this->asteroids.reserve(this->number_of_asteroids);
	this->lights.reserve(this->number_of_lights);

	CreateLevel();
	CreatePlayer(false);

	this->short_sound->SetVolume(0.3f);

	this->background_sound->SetVolume(0.4f);
	this->background_sound->Loop(true);
	//this->background_sound->Play();

	Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &Demo::OnStartKeyPressCallback, "StartCallback");
}

Demo::~Demo()
{
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "StartCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "RestartCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "PlayCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyReleased, "PlayCallback");
	Pear::Commands::End();
}

void Demo::OnUpdate(const float time_step)
{
	using namespace Pear;

	static float time = 0.0f;
	time += time_step;

	Commands::StartFrame(this->camera, time_step);

	Commands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	DrawText(time);

	if (glm::fmod(time, 8.0f) < 0.05f)
	{
		LOG("Pushed asteroids")
		PushAsteroids();
	}

	Commands::DrawRectangle(
		{ 0.0f, 0.0f, -0.9f }, 
		{ static_cast<float>(this->level_width) + 20.0f, static_cast<float>(this->level_height) + 20.0f },
		background_texture, 
		0.0f, 
		3.5f
	);

	for (const auto& asteroid : asteroids)
		asteroid->SetRotation(asteroid->GetRotation() + glm::radians(Commands::RandomNumber() * 20.0f * time_step));

	MovePlayer();
	DrawLights();

	Commands::EndFrame();

	camera.SetPosition({ player->GetPosition(), 0.0f });
}

void Demo::CreateProjectile(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, const float rotation) const
{
	const auto obj = Pear::Commands::CreatePhysicsObject(
		position,
		size,
		{ 0.93f, 0.54f, 0.16f, 1.0f },
		velocity,
		1.0f,
		1.0f
	);
	obj->SetOnCollisionCallback([](const std::shared_ptr<Pear::CollisionObject>& col_obj, const std::shared_ptr<Pear::CollisionObject>& other_obj) {
		if (!other_obj->GetIsTrigger())
			Pear::Commands::RemovePhysicsObject(col_obj);
		});
	this->player->SetRotation(rotation);
	this->short_sound->Restart();
}

void Demo::DrawText(const float time) const
{
	using namespace Pear;

	if (this->is_start_menu && glm::fmod(time, 1.0f) < 0.5f)
	{
		Commands::DrawText("Press \"space\" to start", { -0.42f, 0.0f }, 1.5f, { 1.0f, 1.0f, 1.0f });
	}
	else if (this->is_playing)
	{
		Commands::DrawText("Score: " + std::to_string(this->score), { -0.2f, 0.9f }, 1.5f, { 1.0f, 1.0f, 1.0f });
	}
	else if (this->is_game_over)
	{
		Commands::DrawText("Your score was " + std::to_string(this->score), { -0.32f, 0.2f }, 1.5f, { 1.0f, 1.0f, 1.0f });
		if (glm::fmod(time, 1.0f) < 0.5f)
		{
			Commands::DrawText("Press \"R\" to restart", { -0.42f, 0.0f }, 1.5f, { 1.0f, 1.0f, 1.0f });
		}
	}
}

void Demo::PushAsteroids() const
{
	for (const auto& asteroid : this->asteroids)
	{
		asteroid->SetAcceleration(asteroid->GetAcceleration() + Pear::Commands::RandomNumber(-1.0f, 1.0f));
	}
}

void Demo::DrawLights()
{
	for (const auto& [pos, radius, color] : this->lights)
	{
		Pear::Commands::DrawLightSource(pos, radius, color);
	}
}

void Demo::MovePlayer()
{
	using namespace Pear;

	glm::vec2 position{};
	glm::vec2 velocity{};

	if (this->up)
	{
		position = { player->GetPosition().x + (Commands::RandomNumber() - 0.5f) * 0.3f, player->GetPosition().y - 0.25f };
		velocity = { 0.0f, -0.5f };
		this->player->SetRotation(0.0f);
		if (this->player_direction == Horizontal)
		{
			this->player->SwapSize();
			this->player_direction = Vertical;
		}
	}
	else if (this->down)
	{
		position = { player->GetPosition().x + (Commands::RandomNumber() - 0.5f) * 0.3f, player->GetPosition().y + 0.25f };
		velocity = { 0.0f, 0.5f };
		this->player->SetRotation(glm::radians(-180.f));
		if (this->player_direction == Horizontal)
		{
			this->player->SwapSize();
			this->player_direction = Vertical;
		}
	}
	else if (this->left)
	{
		position = { player->GetPosition().x + 0.25f, player->GetPosition().y + (Commands::RandomNumber() - 0.5f) * 0.3f };
		velocity = { 0.5f, 0.0f };
		this->player->SetRotation(glm::radians(90.f));
		if (this->player_direction == Vertical)
		{
			this->player->SwapSize();
			this->player_direction = Horizontal;
		}
	}
	else if (this->right)
	{
		position = { player->GetPosition().x - 0.25f, player->GetPosition().y + (Commands::RandomNumber() - 0.5f) * 0.3f };
		velocity = { -0.5f, 0.0f };
		this->player->SetRotation(glm::radians(-90.f));
		if (this->player_direction == Vertical)
		{
			this->player->SwapSize();
			this->player_direction = Horizontal;
		}
	}

	if (this->up || this->down || this->left || this->right)
	{
		Commands::DrawParticle({
		.position = position,
		.velocity = velocity,
		.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
		.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
		.start_size = { 0.2f, 0.2f },
		.end_size = {0.1f, 0.1f},
		.rotation = 0.5f,
		.life_time = 1.0f
			});
	}
}

void Demo::AddScore()
{
	++this->score;
}

void Demo::CreateLevel()
{
	CreateLights(this->number_of_lights);
	CreateAsteroids(this->number_of_asteroids);
	CreateCollectibles(this->number_of_collectibles);
	CreateLevelBounds(this->level_width, this->level_height);
}

void Demo::CreateLights(const int amount)
{
	using namespace Pear;

	this->lights.clear();

	const float limit_x = static_cast<float>(this->level_width) / 2.0f - 1.0f;
	const float limit_y = static_cast<float>(this->level_height) / 2.0f - 1.0f;

	for (int i = 0; i < amount; ++i)
	{
		const float pos_x = Commands::RandomNumber(-limit_x, limit_x);
		const float pos_y = Commands::RandomNumber(-limit_y, limit_y);
		const float radius = Commands::RandomNumber(1.0f, 8.0f);
		const float color_r = Commands::RandomNumber(0.1f, 0.9f);
		const float color_g = Commands::RandomNumber(0.1f, 0.9f);
		const float color_b = Commands::RandomNumber(0.1f, 0.9f);

		this->lights.emplace_back(std::tuple{ glm::vec2{pos_x, pos_y }, radius, glm::vec3{ color_r, color_g, color_b} });
	}
}

bool Demo::OnPlayKeyPressCallback(const Pear::EventData data)
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_F)
	{
		const bool fullscreen = Pear::Commands::IsWindowFullscreen();
		Pear::Commands::MakeWindowFullscreen(!fullscreen);
	}
	else if (keycode == GLFW_KEY_RIGHT)
	{
		CreateProjectile({ player->GetPosition().x + 0.5f, player->GetPosition().y }, 
			{ 0.15f, 0.05f }, { 20.0f, 0.0f }, glm::radians(-90.f));
	}
	else if (keycode == GLFW_KEY_LEFT)
	{
		CreateProjectile({ player->GetPosition().x - 0.5f, player->GetPosition().y }, 
			{ 0.15f, 0.05f }, { -20.0f, 0.0f }, glm::radians(90.f));
	}
	else if (keycode == GLFW_KEY_UP)
	{
		CreateProjectile({ player->GetPosition().x, player->GetPosition().y + 0.5f }, 
			{ 0.05f, 0.15f }, { 0.0f, 20.0f }, glm::radians(0.0f));
	}
	else if (keycode == GLFW_KEY_DOWN)
	{
		CreateProjectile({ player->GetPosition().x, player->GetPosition().y - 0.5f }, 
			{ 0.05f, 0.15f }, { 0.0f, -20.0f }, glm::radians(180.0f));
	}
	else if (keycode == GLFW_KEY_W)
	{
		this->up = true;
	}
	else if (keycode == GLFW_KEY_S)
	{
		this->down = true;
	}
	else if (keycode == GLFW_KEY_A)
	{
		this->left = true;
	}
	else if (keycode == GLFW_KEY_D)
	{
		this->right = true;
	}
	return true;
}

bool Demo::OnPlayKeyReleaseCallback(const Pear::EventData data)
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_W)
	{
		this->up = false;
	}
	else if (keycode == GLFW_KEY_S)
	{
		this->down = false;
	}
	else if (keycode == GLFW_KEY_A)
	{
		this->left = false;
	}
	else if (keycode == GLFW_KEY_D)
	{
		this->right = false;
	}
	return true;
}

void Demo::CreatePlayer(const bool is_controllable)
{
	this->player = Pear::Commands::CreatePlayer({ 0.15f, 0.4f }, this->player_texture);
	this->player->SetIsControllable(is_controllable);
	this->player->SetOnCollisionCallback([&](const std::shared_ptr<Pear::CollisionObject>& player_obj, 
		const std::shared_ptr<Pear::CollisionObject>& other_obj)
	{
		if (other_obj->GetIsTrigger() || !other_obj->GetIsKinematic())
			return;

		Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "PlayCallback");
		Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyReleased, "PlayCallback");
		Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &Demo::OnRestartKeyPressCallback, "RestartCallback");

		this->is_game_over = true;
		this->is_playing = false;

		this->up = false;
		this->down = false;
		this->left = false;
		this->right = false;

		Pear::Commands::RemovePhysicsObject(player_obj);
	});
	this->player_direction = Vertical;
}

void Demo::CreateAsteroids(const int amount)
{
	using namespace Pear;

	for (const auto& asteroid : this->asteroids)
	{
		Commands::RemovePhysicsObject(asteroid);
	}
	this->asteroids.clear();

	const float limit_x = static_cast<float>(this->level_width) / 2.0f - 1.0f;
	const float limit_y = static_cast<float>(this->level_height) / 2.0f - 1.0f;

	for (int i = 0; i < amount; ++i)
	{
		const float pos_x = Commands::RandomNumber(-limit_x, limit_x);
		const float pos_y = Commands::RandomNumber(-limit_y, limit_y);
		const float size = Commands::RandomNumber(0.5f, 2.0f);
		const float force_x = Commands::RandomNumber(-1.5f, 1.5f);
		const float force_y = Commands::RandomNumber(-1.5f, 1.5f);
		const float restitution = Commands::RandomNumber(0.0f, 0.5f);
		constexpr float slow_down_factor = 1.0f;

		// If the distance is to close to player spawn position, skip this iteration
		if (constexpr float threshold = 2.0f; 
			pos_x < threshold && pos_x > -threshold && 
			pos_y < threshold && pos_y > -threshold)
		{
			LOG("Asteroid position x: {}, y: {}", pos_x, pos_y)
			--i;
			continue;
		}

		const auto asteroid = Commands::CreatePhysicsObject(
			{ pos_x, pos_y },
			{ size, size },
			this->asteroid_texture,
			{ force_x, force_y },
			restitution,
			slow_down_factor,
			false
		);

		this->asteroids.emplace_back(asteroid);
	}
}

void Demo::CreateCollectibles(const int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		CreateCollectible();
	}
}

void Demo::CreateCollectible()
{
	const float limit_x = static_cast<float>(this->level_width) / 2.0f - 1.0f;
	const float limit_y = static_cast<float>(this->level_height) / 2.0f - 1.0f;

	const float pos_x = Pear::Commands::RandomNumber(-limit_x, limit_x);
	const float pos_y = Pear::Commands::RandomNumber(-limit_y, limit_y);

	const auto trigger = Pear::Commands::CreateTrigger(
		{ pos_x, pos_y },
		{ 0.2f, 0.2f },
		{ 0.87f, 0.98f, 0.01f, 1.0f },
		false
	);
	trigger->SetOnCollisionCallback([&](const std::shared_ptr<Pear::CollisionObject>& trigger_obj,
		const std::shared_ptr<Pear::CollisionObject>& other_obj)
	{
		if (!other_obj->GetIsControllable())
			return;

		static bool got_score{};
		Pear::Commands::RemoveTrigger(trigger_obj);
		if (!got_score)
		{
			AddScore();
			CreateCollectible();
			got_score = !got_score;
		}
		else
		{
			got_score = !got_score;
		}
	});
}

void Demo::CreateLevelBounds(int width, const int height) const
{
	const glm::vec4 color = { 0.4f, 0.7f, 0.5f, 0.0f };
	const glm::vec2 force = { 0.0f, 0.0f };
	constexpr float restitution = 1.0f;
	constexpr float slow_down_factor = 1.0f;
	constexpr bool has_shadow = false;
	constexpr bool is_kinematic = false;

	Pear::Commands::CreatePhysicsObject(
		{ 0.0f, static_cast<float>(height) / 2.0f },
		{ width, 0.5f },
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	);

	Pear::Commands::CreatePhysicsObject(
		{ -static_cast<float>(width) / 2.0f, 0.0f },
		{ 0.5f, height},
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	);

	Pear::Commands::CreatePhysicsObject(
		{ 0.0f, -static_cast<float>(height) / 2.0f },
		{ width, 0.5f },
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	);

	Pear::Commands::CreatePhysicsObject(
		{ static_cast<float>(width) / 2.0f, 0.0f },
		{ 0.5f, height },
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	);
}

bool Demo::OnStartKeyPressCallback(const Pear::EventData data)
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_SPACE)
	{
		this->is_playing = true;
		this->is_start_menu = false;
		this->player->SetIsControllable(true);
		Pear::Commands::UpdatePhysics(true);
		Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "StartCallback");
		Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &Demo::OnPlayKeyPressCallback, "PlayCallback");
		Pear::Commands::SubscribeToEvent(Pear::EventType::KeyReleased, this, &Demo::OnPlayKeyReleaseCallback, "PlayCallback");
	}

	return true;
}

[[nodiscard]] bool Demo::OnRestartKeyPressCallback(const Pear::EventData data)
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_R)
	{
		this->is_playing = true;
		this->is_game_over= false;

		this->score = 0;

		CreatePlayer(true);
		CreateLevel();

		Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &Demo::OnPlayKeyPressCallback, "PlayCallback");
		Pear::Commands::SubscribeToEvent(Pear::EventType::KeyReleased, this, &Demo::OnPlayKeyReleaseCallback, "PlayCallback");
		Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "RestartCallback");
	}
	return true;
}

std::unique_ptr<Pear::Application> Pear::CreateUserApp()
{
	return std::make_unique<Demo>();
}
