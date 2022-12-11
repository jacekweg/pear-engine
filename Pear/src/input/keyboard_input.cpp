#include "pch.hpp"
#include "utils/logging.hpp"

#include "keyboard_input.hpp"
#include "events/event.hpp"
#include "events/event_controller.hpp"

#include <GLFW/glfw3.h>

namespace Pear
{
	bool KeyboardInput::KeyPressedCallback(const EventData data)
	{
		if (const int keycode = data.i32[0]; keycode == GLFW_KEY_ESCAPE)
		{
			EventController::FireEvent(EventType::WindowClosed, { .b = true });
		}

		LOG("Key pressed")
		return true;
	}

	bool KeyboardInput::KeyReleasedCallback(const EventData data)
	{
		LOG("Key released")
		return true;
	}
}