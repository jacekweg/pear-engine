#pragma once
#include <application.hpp>

class Demo final : public Pear::Application
{
public:
	Demo();
	~Demo() override;
	Demo(const Demo&) = delete;
	Demo& operator=(const Demo&) = delete;
	Demo(Demo&&) = delete;
	Demo& operator=(Demo&&) = delete;

	void OnUpdate(float time_step) override;

	[[nodiscard]] bool SoundPlayCallback(Pear::EventData data);
	[[nodiscard]] bool KeyReleaseCallback(Pear::EventData data);

private:
	Pear::Camera camera{};

	std::shared_ptr<Pear::Texture> player_texture{}, asteroid_texture{}, background_texture{};

	std::unique_ptr<Pear::Sound> short_sound{}, background_sound{};

	std::shared_ptr<Pear::CollisionObject> player{};

	bool up{}, down{}, left{}, right{};
	int score{};

	std::vector< std::shared_ptr<Pear::CollisionObject>> asteroids{};
};
