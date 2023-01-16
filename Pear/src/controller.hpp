#pragma once
#include "pch.hpp"

#include "gui/window.hpp"
#include "application.hpp"

namespace Pear
{
	/**
	 * @class Controller
	 * @brief The main controller of the engine.
	 */
	class Controller
	{
	public:
		/**
		 * @brief Constructs a new Controller object.
		 */
		Controller();
		/**
		 * @brief Destructs the Controller object.
		 */
		~Controller() = default;

		// Deleted copy and move constructors and assignment operators
		Controller(const Controller&) = delete;
		Controller& operator=(const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(Controller&&) = delete;

		/**
		 * @brief Starts the engine.
		 */
		void Run();
		/**
		 * @brief Stops the engine.
		 */
		void Stop() { this->is_running = false; }

		/**
		 * @brief Returns the singleton instance of the controller.
		 *
		 * @return The singleton instance of the controller.
		 */
		static Controller& GetInstance() { return *static_instance; }

		/**
		 * @brief Returns a reference to the window object.
		 *
		 * @return A reference to the window object.
		 */
		[[nodiscard]] Window& GetWindow() const { return *window; }

	private:
		static Controller* static_instance;
		bool is_running = true;
		float last_frame_time = 0.0f;
		std::unique_ptr<Window> window;
		std::unique_ptr<Application> app;
	};
}
