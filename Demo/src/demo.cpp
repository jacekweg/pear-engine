#include <pear.hpp>

#include "demo.hpp"

#include "graphics/text/text.hpp"
#include "utils/logging.hpp"
#include "utils/random.hpp"

Demo::Demo()
{
	Pear::Commands::Start();

	Pear::Commands::SetWindowName("My app");
	Pear::Commands::ChangeWindowSize(2560, 1600);

	this->short_sound = Pear::Commands::LoadSoundFromFile("res/audio/short.mp3");
	this->background_sound = Pear::Commands::LoadSoundFromFile("res/audio/background.mp3");

	this->player_texture = Pear::Commands::LoadTextureFromFile("res/textures/spaceship.png");
	this->asteroid_texture = Pear::Commands::LoadTextureFromFile("res/textures/asteroid.png");
	this->background_texture = Pear::Commands::LoadTextureFromFile("res/textures/background.png");

	//Pear::Commands::CreatePhysicsObject(
	//	{ 2.5f, -2.0f },
	//	{ 2.0f, 0.5f },
	//	{ 0.43f, 0.54f, 0.56f, 1.0f },
	//	{ 0.0f, 0.0f },
	//	0.0f,
	//	0.0f,
	//	false,
	//	false
	//);

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ 3.5f, 0.5f },
		{ 0.5f, 0.5f },
		this->asteroid_texture,
		{ 0.0f, 0.0f },
		1.0f,
		1.0f,
		false,
		true
	));

	Pear::Commands::CreatePhysicsObject(
		{ 0.1f, -2.0f },
		{ 1.0f, 1.0f },
		this->asteroid_texture,
		{ 0.1f, 0.1f },
		0.01f,
		0.85f,
		false,
		true
	);

	const auto obj_collide = Pear::Commands::CreatePhysicsObject(
		{ 2.5f, 3.0f },
		{ 0.4f, 0.4f },
		this->asteroid_texture,
		{ 0.3f ,-0.6f},
		1.0f,
		0.99f,
		false
	);
	obj_collide->SetOnCollisionCallback([&](const std::shared_ptr<Pear::CollisionObject>& obj)
		{
			obj->SetForce(-obj->GetForce());
			obj->SetVelocity(-obj->GetVelocity());
		});

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ 2.5f, 1.5f },
		{ 0.2f, 0.2f },
		this->asteroid_texture,
		{ 0.0f, 0.2f },
		1.0f,
		0.95f,
		false
	));

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ -2.5f, -0.5f },
		{ 0.3f, 0.3f },
		this->asteroid_texture,
		{ 0.0f, 0.4f },
		1.0f,
		0.95f,
		false
	));

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ 0.5f, 0.5f },
		{ 0.3f, 0.3f },
		this->asteroid_texture,
		{ 0.0f, 0.0f },
		0.1f,
		1.0f,
		false
	));

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ 1.5f, 0.5f },
		{ 0.3f, 0.3f },
		this->asteroid_texture,
		{ 0.0f, 0.0f },
		0.7f,
		1.0f,
		false
	));

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ -0.5f, -1.5f },
		{ 0.1f, 0.1f },
		this->asteroid_texture,
		{ 0.2f, 0.2f },
		1.0f,
		0.95f,
		false
	));

	this->asteroids.emplace_back(Pear::Commands::CreatePhysicsObject(
		{ -1.0f, -0.6f },
		{ 0.5f, 0.5f },
		this->asteroid_texture,
		{ -0.2f, -0.3f },
		1.0f,
		0.95f,
		false
	));

	player = Pear::Commands::CreatePlayer(
		{ 0.15f, 0.4f },
		this->player_texture
	);

	const auto trigger = Pear::Commands::CreateTrigger(
		{ 0.5, 2.0f },
		{ 0.2f, 0.2f },
		{ 0.87f, 0.98f, 0.01f, 1.0f },
		false
	);
	trigger->SetOnCollisionCallback([&](const std::shared_ptr<Pear::CollisionObject>& trigger_obj)
		{
			static bool got_score{};
			Pear::Commands::RemoveTrigger(trigger_obj);
			if (!got_score)
			{
				LOG("You score is {}", ++this->score)
					got_score = !got_score;
			}
		});

	this->short_sound->SetVolume(0.3f);

	this->background_sound->SetVolume(0.4f);
	this->background_sound->Loop(true);
	//this->background_sound->Play();

	Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &Demo::SoundPlayCallback, "SoundCallback");
	Pear::Commands::SubscribeToEvent(Pear::EventType::KeyReleased, this, &Demo::KeyReleaseCallback, "SoundCallback");
}

Demo::~Demo()
{
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "SoundCallback");
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyReleased, "SoundCallback");
	Pear::Commands::End();
}

void Demo::OnUpdate(const float time_step)
{
	using namespace Pear;

	static float time = 0.0f;

	Commands::StartFrame(this->camera, time_step);

	time += time_step;

	Commands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	//Commands::DrawShadowRectangle(
	//	{ 2.0f * -glm::cos(time) + 5.0f, -0.5f, 0.0f },
	//	{ 0.5f, 0.5f },
	//	{ 0.87f, 0.23f, 0.27f, 1.0f },
	//	glm::pi<float>() * glm::cos(time)
	//);

	//Commands::DrawLightSource({ 2.0f * glm::cos(time) + 0.5f, -3.0f }, 2.0f, { 1.0f, 0.0f, 1.0f });
	Commands::DrawLightSource({ 4.5f, 0.5f }, 3.0f, { 0.0f, 1.0f, 1.0f });
	Commands::DrawLightSource({ 12.5f, -5.5f }, 3.0f, { 1.0f, 1.0f, 0.0f });
	Commands::DrawLightSource({ -3.5f, 1.5f }, 5.0f, { 0.5f, 0.6f, 0.1f });

	Commands::DrawRectangle({ 0.0f, 0.0f, -0.9f }, { 50.0f, 50.0f }, background_texture, 0.6f, 2.0f);

	//Commands::DrawRectangle({ -0.9f, -1.0f, -0.1f }, { 1.0f, 1.0f }, asteroid_texture, 0.3f);

	Commands::DrawText("This is sample text", { 25.0f, 25.0f }, 1.0f, { 1.0f, 1.0f, 1.0f });

	if (this->up)
	{
		Commands::DrawParticle({
		.position = { player->GetPosition().x + (Random::Generate() - 0.5f) * 0.3f, player->GetPosition().y - 0.25f},
		.velocity = {0.0f, -0.5f},
		.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
		.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
		.start_size = { 0.2f, 0.2f },
		.end_size = {0.1f, 0.1f},
		.rotation = 0.5f,
		.life_time = 1.0f
		});
		this->player->SetRotation(0.0f);
	}
	else if (this->down)
	{
		Commands::DrawParticle({
		.position = { player->GetPosition().x + (Random::Generate() - 0.5f) * 0.3f, player->GetPosition().y + 0.25f},
		.velocity = {0.0f, 0.5f},
		.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
		.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
		.start_size = { 0.2f, 0.2f },
		.end_size = {0.1f, 0.1f},
		.rotation = 0.5f,
		.life_time = 1.0f
		});
		this->player->SetRotation(glm::radians(-180.f));

	}
	else if (this->left)
	{
		Commands::DrawParticle({
		.position = { player->GetPosition().x + 0.25f, player->GetPosition().y + (Random::Generate() - 0.5f) * 0.3f},
		.velocity = {0.5f, 0.0f},
		.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
		.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
		.start_size = { 0.2f, 0.2f },
		.end_size = {0.1f, 0.1f},
		.rotation = 0.5f,
		.life_time = 1.0f
		});
		this->player->SetRotation(glm::radians(90.f));

	}
	else if (this->right)
	{
		Commands::DrawParticle({
		.position = { player->GetPosition().x - 0.25f, player->GetPosition().y + (Random::Generate() - 0.5f) * 0.3f},
		.velocity = {-0.5f, 0.0f},
		.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
		.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
		.start_size = { 0.2f, 0.2f },
		.end_size = {0.1f, 0.1f},
		.rotation = 0.5f,
		.life_time = 1.0f
		});
		this->player->SetRotation(glm::radians(-90.f));

	}

	for (const auto& asteroid : asteroids)
		asteroid->SetRotation(asteroid->GetRotation() + glm::radians(Random::Generate() * 20.0f * time_step));

	Commands::EndFrame();
	camera.SetPosition({ player->GetPosition(), 0.0f });

}

bool Demo::SoundPlayCallback(const Pear::EventData data)
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_F)
	{
		const bool fullscreen = Pear::Commands::IsWindowFullscreen();
		Pear::Commands::MakeWindowFullscreen(!fullscreen);
	}
	else if (keycode == GLFW_KEY_RIGHT)
	{
		const auto obj = Pear::Commands::CreatePhysicsObject(
			{ player->GetPosition().x + 0.5f, player->GetPosition().y},
			{ 0.15f, 0.05f, },
			{ 0.93f, 0.54f, 0.16f, 1.0f },
			{ 20.0f, 0.0f },
			1.0f,
			1.0f
		);
		obj->SetOnCollisionCallback([](const std::shared_ptr<Pear::CollisionObject>& col_obj)
			{
				Pear::Commands::RemovePhysicsObject(col_obj);
			});
		this->player->SetRotation(glm::radians(-90.f));
		this->short_sound->Restart();

	}
	else if (keycode == GLFW_KEY_LEFT)
	{
		const auto obj = Pear::Commands::CreatePhysicsObject(
			{ player->GetPosition().x - 0.5f, player->GetPosition().y },
			{ 0.15f, 0.05f, },
			{ 0.93f, 0.54f, 0.16f, 1.0f },
			{ -20.0f, 0.0f },
			1.0f,
			1.0f
		);
		obj->SetOnCollisionCallback([](const std::shared_ptr<Pear::CollisionObject>& col_obj)
			{
				Pear::Commands::RemovePhysicsObject(col_obj);
			});
		this->player->SetRotation(glm::radians(90.f));
		this->short_sound->Restart();

	}
	else if (keycode == GLFW_KEY_UP)
	{
		const auto obj = Pear::Commands::CreatePhysicsObject(
			{ player->GetPosition().x, player->GetPosition().y + 0.5f },
			{ 0.05f, 0.15f },
			{ 0.93f, 0.54f, 0.16f, 1.0f },
			{ 0.0f, 20.0f },
			1.0f,
			1.0f
		);
		obj->SetOnCollisionCallback([](const std::shared_ptr<Pear::CollisionObject>& col_obj)
			{
				Pear::Commands::RemovePhysicsObject(col_obj);
			});
		this->player->SetRotation(glm::radians(0.0f));
		this->short_sound->Restart();

	}
	else if (keycode == GLFW_KEY_DOWN)
	{
		const auto obj = Pear::Commands::CreatePhysicsObject(
			{ player->GetPosition().x, player->GetPosition().y - 0.5f },
			{ 0.05f, 0.15f },
			{ 0.93f, 0.54f, 0.16f, 1.0f },
			{ 0.0f, -20.0f },
			1.0f,
			1.0f
		);
		obj->SetOnCollisionCallback([](const std::shared_ptr<Pear::CollisionObject>& col_obj)
			{
				Pear::Commands::RemovePhysicsObject(col_obj);
			});
		this->player->SetRotation(glm::radians(180.0f));
		this->short_sound->Restart();

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

bool Demo::KeyReleaseCallback(const Pear::EventData data)
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

std::unique_ptr<Pear::Application> Pear::CreateUserApp()
{
	return std::make_unique<Demo>();
}
