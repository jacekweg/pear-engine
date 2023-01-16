#pragma once
#include <application.hpp>

/**
 * @class Demo
 * @brief Demo game to show the engine capabilities.
 * @extends Pear::Application
 */
class Demo final : public Pear::Application
{
public:
	/**
	 * @brief Constructs the Demo class.
	 */
	Demo();
	/**
	 * @brief Destroys the Demo class.
	 */
	~Demo() override;

	// Deleted copy and move constructors and assignment operators
	Demo(const Demo&) = delete;
	Demo& operator=(const Demo&) = delete;
	Demo(Demo&&) = delete;
	Demo& operator=(Demo&&) = delete;

	/**
	 * @brief Method to be called every frame.
	 *
	 * @param time_step The time step between the current frame and the last frame.
	 */
	void OnUpdate(float time_step) override;

	/**
	 * @brief The callback function for toggling the fullscreen mode on and off.
	 *
	 * @param data The event data.
	 * @return true if the event was handled and false otherwise.
	 */
	[[nodiscard]] static bool OnFullscreenCallback(Pear::EventData data);

	/**
	 * @brief The callback function for the key press event at the start screen.
	 *
	 * @param data The event data.
	 * @return true if the event was handled and false otherwise.
	 */
	[[nodiscard]] bool OnStartKeyPressCallback(Pear::EventData data);
	/**
	 * @brief The callback function for the key press event at the restart screen.
	 *
	 * @param data The event data.
	 * @return true if the event was handled and false otherwise.
	 */
	[[nodiscard]] bool OnRestartKeyPressCallback(Pear::EventData data);

	/**
	 * @brief The callback function for the key press event, while the game is in progress.
	 *
	 * @param data The event data.
	 * @return true if the event was handled and false otherwise.
	 */
	[[nodiscard]] bool OnPlayKeyPressCallback(Pear::EventData data);
	/**
	 * @brief The callback function for the key release event, while the game is in progress.
	 *
	 * @param data The event data
	 * @return true if the event was handled and false otherwise.
	 */
	[[nodiscard]] bool OnPlayKeyReleaseCallback(Pear::EventData data);
private:
	/**
	 * @brief Creates the level.
	 */
	void CreateLevel();
	/**
	 * @brief Creates the lights.
	 *
	 * @param amount The number of lights to create.
	 */
	void CreateLights(int amount);
	/**
	 * @brief Creates the asteroids.
	 *
	 * @param amount The number of asteroids to create.
	 */
	void CreateAsteroids(int amount);
	/**
	 * @brief Create the collectibles.
	 *
	 * @param amount The number of collectibles to create.
	 */
	void CreateCollectibles(int amount);
	/**
	 * @brief Creates a single collectible.
	 */
	void CreateCollectible();
	/**
	 * @brief Creates the player.
	 *
	 * @param is_controllable Whether the player is controllable or not.
	 */
	void CreatePlayer(bool is_controllable);
	/**
	 * @brief Creates the level bounds.
	 *
	 * @param width The width of the level.
	 * @param height The height of the level.
	 */
	void CreateLevelBounds(int width, int height) const;
	/**
	 * @brief Creates a projectile.
	 *
	 * @param position The position of the projectile.
	 * @param size The size of the projectile.
	 * @param velocity The velocity of the projectile.
	 * @param rotation The rotation of the projectile.
	 */
	void CreateProjectile(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, float rotation) const;

	/**
	 * @brief Regenerates the objects in the level.
	 */
	void RestartLevel();

	/**
	 * @brief Add one to the player score.
	 */
	void AddScore();
	/**
	 * @brief Draws the lights.
	 */
	void DrawLights();
	/**
	 * @brief Moves the player.
	 */
	void MovePlayer();
	/**
	 * @brief Pushes the asteroids.
	 */
	void PushAsteroids() const;
	/**
	 * @brief Draws the text.
	 *
	 * @param time The current time.
	 */
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
