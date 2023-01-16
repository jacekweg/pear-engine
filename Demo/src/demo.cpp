#include <pear.hpp>

#include "demo.hpp"

Demo::Demo()
{
	Pear::Commands::Start();

	Pear::Commands::SetWindowName("Demo game");
	Pear::Commands::ChangeWindowSize(2560, 1600);

	this->camera.SetMaxZoom(6.5f);
	this->camera.SetMinZoom(1.0f);

	this->shoot_sound = Pear::Commands::LoadSoundFromFile("res/audio/shoot.wav");
	this->thrust_sound = Pear::Commands::LoadSoundFromFile("res/audio/thrust.wav");
	this->pickup_sound = Pear::Commands::LoadSoundFromFile("res/audio/pickup.wav");
	this->explosion_sound = Pear::Commands::LoadSoundFromFile("res/audio/explosion.wav");

	this->player_texture = Pear::Commands::LoadTextureFromFile("res/textures/spaceship.png");
	this->asteroid_texture = Pear::Commands::LoadTextureFromFile("res/textures/asteroid.png");
	this->background_texture = Pear::Commands::LoadTextureFromFile("res/textures/background.png");

	this->coin_textures.emplace_back(Pear::Commands::LoadTextureFromFile("res/textures/coin.png"));
	this->coin_textures.emplace_back(Pear::Commands::LoadTextureFromFile("res/textures/coin_2.png"));
	this->coin_textures.emplace_back(Pear::Commands::LoadTextureFromFile("res/textures/coin_3.png"));
	this->coin_textures.emplace_back(Pear::Commands::LoadTextureFromFile("res/textures/coin_4.png"));

	this->asteroids.reserve(this->number_of_asteroids);
	this->lights.reserve(this->number_of_lights);

	CreateLevel();
	CreatePlayer(false);

	this->shoot_sound->SetVolume(0.5f);
	this->explosion_sound->SetVolume(0.8f);
	this->thrust_sound->SetVolume(0.15f);
	this->thrust_sound->Loop(true);

	Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, &Demo::OnFullscreenCallback, "FullscreenCallback");
	Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &Demo::OnStartKeyPressCallback, "StartCallback");
}

Demo::~Demo()
{
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "StartCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "RestartCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "PlayCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyReleased, "PlayCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "FullscreenCallback");

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
		PushAsteroids();
	}

	Commands::DrawRectangle({
		.pos = { 0.0f, 0.0f, -0.9f },
		.size = { static_cast<float>(this->level_width) + 20.0f, static_cast<float>(this->level_height) + 20.0f },
		.texture = background_texture,
		.rotation = 0.0f,
		.tiling_factor = 3.5f
	});

	for (const auto& asteroid : asteroids)
		asteroid->SetRotation(asteroid->GetRotation() + glm::radians(Commands::RandomNumber() * 20.0f * time_step));

	MovePlayer();
	DrawLights();

	Commands::EndFrame();

	camera.SetPosition({ player->GetPosition(), 0.0f });
}

bool Demo::OnFullscreenCallback(const Pear::EventData data)
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_F)
	{
		const bool fullscreen = Pear::Commands::IsWindowFullscreen();
		Pear::Commands::MakeWindowFullscreen(!fullscreen);
	}

	return true;
}

void Demo::CreateProjectile(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, const float rotation) const
{
	const auto obj = Pear::Commands::CreatePhysicsObject({
		.pos = position,
		.size = size,
		.color = { 0.93f, 0.54f, 0.16f, 1.0f },
		.force = velocity,
		.restitution = 1.0f,
		.slow_down_factor = 1.0f
	});
	obj->SetOnCollisionCallback([](const auto& col_obj, const auto& other_obj) {
		if (!other_obj->GetIsTrigger())
			Pear::Commands::RemovePhysicsObject(col_obj);
		});

	this->player->SetRotation(rotation);
	this->shoot_sound->Restart();
}

void Demo::RestartLevel()
{
	CreateLights(this->number_of_lights);
	CreateAsteroids(this->number_of_asteroids);
}

void Demo::DrawText(const float time) const
{
	using namespace Pear;

	if (this->is_start_menu && glm::fmod(time, 1.0f) < 0.5f)
	{
		Commands::DrawText("Press \"space\" to start", { -0.5f, 0.0f }, 1.5f, { 1.0f, 1.0f, 1.0f });
	}
	else if (this->is_playing)
	{
		Commands::DrawText("Score: " + std::to_string(this->score), { -0.2f, 0.9f }, 1.5f, { 1.0f, 1.0f, 1.0f });
	}
	else if (this->is_game_over)
	{
		Commands::DrawText("Your score was " + std::to_string(this->score), { -0.35f, 0.1f }, 1.5f, { 1.0f, 1.0f, 1.0f });
		if (glm::fmod(time, 1.0f) < 0.5f)
		{
			Commands::DrawText("Press \"R\" to restart", { -0.45f, -0.1f }, 1.5f, { 1.0f, 1.0f, 1.0f });
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

	constexpr float player_offset = 0.2f;
	constexpr float spread = 0.2f;

	if (this->up)
	{
		position = { player->GetPosition().x + (Commands::RandomNumber() - 0.5f) * spread, player->GetPosition().y - player_offset };
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
		position = { player->GetPosition().x + (Commands::RandomNumber() - 0.5f) * spread, player->GetPosition().y + player_offset };
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
		position = { player->GetPosition().x + player_offset, player->GetPosition().y + (Commands::RandomNumber() - 0.5f) * spread };
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
		position = { player->GetPosition().x - player_offset, player->GetPosition().y + (Commands::RandomNumber() - 0.5f) * spread };
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
		.start_size = { 0.1f, 0.1f },
		.end_size = {0.01f, 0.01f},
		.rotation = 0.5f,
		.life_time = 1.0f
		});
	}
	else
	{
		this->thrust_sound->Pause();
	}
}

void Demo::AddScore()
{
	++this->score;
}

void Demo::CreateLevel()
{
	Pear::Commands::UpdatePhysics(false);
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
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_RIGHT)
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
		this->thrust_sound->Play();
	}
	else if (keycode == GLFW_KEY_S)
	{
		this->down = true;
		this->thrust_sound->Play();
	}
	else if (keycode == GLFW_KEY_A)
	{
		this->left = true;
		this->thrust_sound->Play();
	}
	else if (keycode == GLFW_KEY_D)
	{
		this->right = true;
		this->thrust_sound->Play();
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
	this->player->SetOnCollisionCallback([&](const auto& player_obj, const auto& other_obj)
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

		this->explosion_sound->Restart();
		this->thrust_sound->Restart();

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

		const auto asteroid = Commands::CreatePhysicsObject({
			.pos = { pos_x, pos_y },
			.size = { size, size },
			.texture = this->asteroid_texture,
			.force = { force_x, force_y },
			.restitution = restitution,
			.slow_down_factor = slow_down_factor,
			.has_shadow = false
		});

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
	static uint64_t texture_idx = 0;

	const float limit_x = static_cast<float>(this->level_width) / 2.0f - 1.0f;
	const float limit_y = static_cast<float>(this->level_height) / 2.0f - 1.0f;

	const float pos_x = Pear::Commands::RandomNumber(-limit_x, limit_x);
	const float pos_y = Pear::Commands::RandomNumber(-limit_y, limit_y);

	const auto trigger = Pear::Commands::CreateTrigger(
		{ pos_x, pos_y },
		{ 0.2f, 0.2f },
		this->coin_textures[texture_idx++],
		false
	);

	texture_idx = texture_idx % this->coin_textures.size();

	trigger->SetOnCollisionCallback([&](const auto& trigger_obj, const auto& other_obj)
	{
		if (!other_obj->GetIsControllable())
			return;

		if (static bool got_score{}; !got_score)
		{
			Pear::Commands::RemoveTrigger(trigger_obj);
			AddScore();
			CreateCollectible();
			this->pickup_sound->Restart();
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

	Pear::Commands::CreatePhysicsObject({
		.pos = { 0.0f, static_cast<float>(height) / 2.0f },
		.size = { width, 0.5f },
		.color = color,
		.force = force,
		.restitution = restitution,
		.slow_down_factor = slow_down_factor,
		.has_shadow = has_shadow,
		.is_kinematic = is_kinematic
	});

	Pear::Commands::CreatePhysicsObject({
		{ -static_cast<float>(width) / 2.0f, 0.0f },
		{ 0.5f, height },
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	});

	Pear::Commands::CreatePhysicsObject({
		{ 0.0f, -static_cast<float>(height) / 2.0f },
		{ width, 0.5f },
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	});

	Pear::Commands::CreatePhysicsObject({
		{ static_cast<float>(width) / 2.0f, 0.0f },
		{ 0.5f, height },
		color,
		force,
		restitution,
		slow_down_factor,
		has_shadow,
		is_kinematic
	});
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
		RestartLevel();

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
