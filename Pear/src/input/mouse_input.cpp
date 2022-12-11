#include "pch.hpp"
#include "utils/logging.hpp"

#include "mouse_input.hpp"
#include "events/event.hpp"

namespace Pear
{
	bool MouseInput::MouseScrolledCallback(const EventData data)
	{
		double y = data.d64;
		LOG("Mouse scrolled: {} offset", y)

		return true;
	}
}
