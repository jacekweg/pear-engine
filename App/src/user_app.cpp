#include <pear.hpp>

#include "user_app.hpp"

UserApp::UserApp()
{
	Pear::Commands::Start();

	Pear::Commands::SetWindowName("My app");
	Pear::Commands::ChangeWindowSize(2560, 1600);

	this->camera.SetIsControllable(true);

	this->alpha_texture = Pear::Commands::LoadTextureFromFile("res/textures/alpha.png");

	Pear::Commands::CreatePhysicsObject({
		{ 3.5f, 0.5f },
		{ 0.5f, 0.5f },
		{ 0.43f, 0.54f, 0.56f, 1.0f },
		{ 0.0f, 0.0f },
		1.0f,
		0.0f,
		false,
		false
	});

	Pear::Commands::CreatePhysicsObject({
		{ 2.5f, 3.0f },
		{ 0.4f, 0.4f },
		{ 0.43f, 0.54f, 0.56f, 1.0f },
		{ 0.0f, 0.0f },
		0.3f,
		1.0f
	});

	const auto test = Pear::Commands::CreatePhysicsObject({
		{ 2.5f, 1.5f },
		{ 0.5f, 0.5f },
		{ 0.83f, 0.54f, 0.56f, 1.0f },
		{ 0.0f, -1.0f },
		1.0f,
		1.0f
	});
	test->SetOnCollisionCallback([](const auto& obj, const auto& second_obj)
		{
			obj->SetAcceleration(-obj->GetAcceleration() * 0.5f);
		});

	movable = Pear::Commands::CreatePhysicsObject({
		{ 0.0f, 1.0f },
		{ 0.5f, 0.5f },
		this->checker_texture,
		{ 0.0f, 0.0f },
		1.0f,
		0.5f,
		true
	});
	movable->SetIsControllable(false);

	this->short_sound = Pear::Commands::LoadSoundFromFile("res/audio/short.mp3");
	this->background_sound = Pear::Commands::LoadSoundFromFile("res/audio/background.mp3");
	
	this->short_sound->SetVolume(0.4f);
	
	this->background_sound->SetVolume(0.4f);
	this->background_sound->Loop(true);
	this->background_sound->Play();

	Pear::Commands::SubscribeToEvent(Pear::EventType::KeyPressed, this, &UserApp::SoundPlayCallback, "SoundCallback");
}

UserApp::~UserApp()
{
	Pear::Commands::UnsubscribeFromEvent(Pear::EventType::KeyPressed, "SoundCallback");
	Pear::Commands::End();
}

void UserApp::OnUpdate(const float time_step)
{
	using namespace Pear;

	static float time = 0.0f;

	Commands::StartFrame(this->camera, time_step);
	time += time_step;

	Commands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	Commands::DrawLightSource({ 4.0f * glm::cos(time) + 5.0f, -0.8f }, 5.0f, { 1.0f, 0.0f, 1.0f });
	Commands::DrawLightSource({ 6.5f, 0.5f }, 5.0f, { 0.0f, 1.0f, 1.0f });
	Commands::DrawLightSource({ 3.5f, 0.5f }, 5.0f, { 1.0f, 1.0f, 0.0f });


	Commands::DrawShadowRectangle(
		{ 2.0f * -glm::cos(time) + 5.0f, -0.5f, 0.0f },
		{ 0.5f, 0.5f },
		{ 0.87f, 0.23f, 0.27f, 1.0f },
		glm::pi<float>() * glm::cos(time)
	);

	Commands::DrawRectangle({ { -0.9f, -1.0f, -0.1f }, { 1.0f, 1.0f }, this->alpha_texture, 0.3f });

	for(int i = 0; i < 9; ++i)
	{
		const int rem = i / 3;
		const auto pos_x = static_cast<float>(i % 3);
		const auto pos_y = static_cast<float>(rem);

		Commands::DrawRectangle(
			{ pos_x / 1.5f - 3.5f, pos_y / 1.5f - 2.5f, 0.0f}, 
			{ 0.5f, 0.5f }, 
			{ 0.65f, 0.21f, 0.13f, 1.0f },
			0.0f
		);
	}

	Commands::DrawParticle({
		.position = {glm::cos(time) - 2.5f, glm::sin(time) + 0.5f},
		.velocity = {0.0f, 0.2f},
		.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
		.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
		.start_size = { 0.2f, 0.2f },
		.end_size = {0.1f, 0.1f},
		.rotation = 0.5f,
		.life_time = 3.0f
		});

	Commands::DrawParticle({
	.position = {-2.5f, 0.5f},
	.velocity = {0.0f, 0.5f},
	.start_color = {0.76f, 0.21f, 0.32f, 1.0f},
	.end_color = { 0.87f, 0.91f, 0.85f, 1.0f },
	.start_size = { 0.2f, 0.2f },
	.end_size = {0.1f, 0.1f},
	.rotation = 0.5f,
	.life_time = 3.0f
	});

	Commands::EndFrame();
}

bool UserApp::SoundPlayCallback(const Pear::EventData data) const
{
	if (const int keycode = data.i32[0]; keycode == GLFW_KEY_P)
	{
		this->short_sound->Restart();
	}
	else if (keycode == GLFW_KEY_F)
	{
		const bool fullscreen = Pear::Commands::IsWindowFullscreen();
		Pear::Commands::MakeWindowFullscreen(!fullscreen);
	}
	return true;
}

std::unique_ptr<Pear::Application> Pear::CreateUserApp()
{
	return std::make_unique<UserApp>();
}
