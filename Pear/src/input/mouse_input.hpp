#pragma once

#include "events/event.hpp"

namespace Pear
{
	class MouseInput
	{
	public:
		[[nodiscard]] static bool MouseScrolledCallback(EventData data);
	};
}
