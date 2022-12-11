#pragma once

#include "events/event.hpp"

namespace Pear
{
	class KeyboardInput
	{
	public:
		[[nodiscard]] static bool KeyPressedCallback(EventData data);
		[[nodiscard]] static bool KeyReleasedCallback(EventData data);
	};
}