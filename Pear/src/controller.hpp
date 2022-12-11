#pragma once
#include "pch.hpp"

#include "gui/window.hpp"
#include "application.hpp"

namespace Pear
{
	class Controller
	{
	public:
		Controller();
		~Controller() = default;
		Controller(const Controller&) = delete;
		Controller& operator=(const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(Controller&&) = delete;

		void Run();
		void Stop() { this->is_running = false; }

		static Controller& GetInstance() { return *static_instance; }

		[[nodiscard]] Window& GetWindow() const { return *window; }

	private:
		static Controller* static_instance;
		bool is_running = true;
		float last_frame_time = 0.0f;
		std::unique_ptr<Window> window;
		std::unique_ptr<Application> app;
	};
}
