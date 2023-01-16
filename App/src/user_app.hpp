#pragma once
#include <application.hpp>

/**
 * @class UserApp
 * @brief Sandbox to test new features and benchmark them.
 * @extends Pear::Application
 */
class UserApp final : public Pear::Application
{
public:
	/**
	 * @brief Constructor.
	 */
	UserApp();

	/**
	 * @brief Destructor.
	 */
	~UserApp() override;

	// Deleted copy and move constructors and assignment operators
	UserApp(const UserApp&) = delete;
	UserApp& operator=(const UserApp&) = delete;
	UserApp(UserApp&&) = delete;
	UserApp& operator=(UserApp&&) = delete;

	/**
	 * @brief Method to be called every frame.
	 *
	 * @param time_step The time step between the current frame and the last frame.
	 */
	void OnUpdate(float time_step) override;

	/**
	 * @brief The callback function to test sound.
	 *
	 * @param data The event data.
	 * @return true if the event was handled and false otherwise.
	 */
	[[nodiscard]] bool SoundPlayCallback(Pear::EventData data) const;

private:
	Pear::Camera camera{};

	std::shared_ptr<Pear::Texture> checker_texture{}, alpha_texture{};

	std::unique_ptr<Pear::Sound> short_sound{}, background_sound{};

	std::shared_ptr<Pear::CollisionObject> movable{};
};