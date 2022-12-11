#include "pch.hpp"
#include "utils/logging.hpp"
#include "utils/random.hpp"

#include "controller.hpp"
#include "audio/audio.hpp"
#include "events/event_controller.hpp"
#include "gui/imgui_instance.hpp"
#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"

namespace Pear
{
	Controller* Controller::static_instance = nullptr;

	Controller::Controller()
	{
		ASSERT(!static_instance, "Controller can be initialized only once")
		static_instance = this;

		Audio::Start();
		Random::Init();

		EventController::SubscribeToEvent(EventType::KeyPressed, KeyboardInput::KeyPressedCallback, "KeyPressed");
		EventController::SubscribeToEvent(EventType::KeyReleased, KeyboardInput::KeyReleasedCallback, "KeyReleased");
		EventController::SubscribeToEvent(EventType::MouseWheelScrolled, MouseInput::MouseScrolledCallback, "MousedScrolled");

		this->window = std::make_unique<Window>("Pear", 1920, 1080);
		this->app = CreateUserApp();
	}

	void Controller::Run()
	{
		ImGuiInstance::BeginRender();
		while (is_running)
		{
			const auto time = static_cast<float>(glfwGetTime());
			const float time_step = time - this->last_frame_time;
			this->last_frame_time = time;

			if (time_step < 0.1f)
			{
				/* User app */
				this->app->OnUpdate(time_step);

				/* ImGui */
				ImGuiInstance::OnUpdate(time_step);

				/* GLFW window */
				this->window->OnUpdate();
			}
		}
		ImGuiInstance::EndRender();
	}
}
