#pragma once

namespace Pear
{
	/**
	 * @class Application
	 * @brief An abstract class that represents the user's application.
	 */
	class Application
	{
	public:
		/**
		 * @brief Default constructor.
		 */
		Application() = default;
		/**
		 * @brief Destructor.
		 */
		virtual ~Application() = default;

		// Deleted copy and move constructors and assignment operators
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		/**
		 * @brief Method to be called every frame.
		 *
		 * @param time_step The time step between the current frame and the last frame.
		 */
		virtual void OnUpdate(float time_step) = 0;
	};

	/**
	 * @brief Creates a new user's application.
	 *
	 * @return A unique pointer to the new application.
	 */
	std::unique_ptr<Application> CreateUserApp();
}
