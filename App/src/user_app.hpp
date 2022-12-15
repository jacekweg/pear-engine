#pragma once
#include <application.hpp>

class UserApp final : public Pear::Application
{
public:
	UserApp();
	~UserApp() override;
	UserApp(const UserApp&) = delete;
	UserApp& operator=(const UserApp&) = delete;
	UserApp(UserApp&&) = delete;
	UserApp& operator=(UserApp&&) = delete;

	void OnUpdate(float time_step) override;

	[[nodiscard]] bool SoundPlayCallback(Pear::EventData data) const;

private:
	Pear::Camera camera{};

	std::shared_ptr<Pear::Texture> checker_texture{}, alpha_texture{};

	std::unique_ptr<Pear::Sound> short_sound{}, background_sound{};

	std::shared_ptr<Pear::CollisionObject> movable{};
};