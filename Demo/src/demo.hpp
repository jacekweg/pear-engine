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

	[[nodiscard]] static bool OnFullscreenCallback(Pear::EventData data);

	[[nodiscard]] bool OnStartKeyPressCallback(Pear::EventData data);
	[[nodiscard]] bool OnRestartKeyPressCallback(Pear::EventData data);

	[[nodiscard]] bool OnPlayKeyPressCallback(Pear::EventData data);
	[[nodiscard]] bool OnPlayKeyReleaseCallback(Pear::EventData data);
private:
	void CreateLevel();
	void CreateLights(int amount);
	void CreateAsteroids(int amount);
	void CreateCollectibles(int amount);
	void CreateCollectible();
	void CreatePlayer(bool is_controllable);
	void CreateLevelBounds(int width, int height) const;
	void CreateProjectile(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, float rotation) const;

	void RestartLevel();

	void AddScore();
	void DrawLights();
	void MovePlayer();
	void PushAsteroids() const;
	void DrawText(float time) const;
private:
	Pear::Camera camera{};

	std::unique_ptr<Pear::Sound> shoot_sound{}, explosion_sound{}, pickup_sound{}, thrust_sound{};
	std::shared_ptr<Pear::Texture> player_texture{}, asteroid_texture{}, background_texture{};
	std::vector<std::shared_ptr<Pear::Texture>> coin_textures{};

	std::shared_ptr<Pear::CollisionObject> player{};
	std::vector<std::shared_ptr<Pear::CollisionObject>> asteroids{};
	std::vector<std::shared_ptr<Pear::CollisionObject>> collectibles{};
	std::vector<std::tuple<glm::vec2, float, glm::vec3>> lights{};

	enum PlayerDirection{ Vertical, Horizontal };
	PlayerDirection player_direction{};

	int score{};
	int level_width = 200, level_height = 100;
	int number_of_asteroids = 50, number_of_lights = 25, number_of_collectibles = 50;
	bool up{}, down{}, left{}, right{};
	bool is_start_menu = true, is_playing{}, is_game_over{};
};
