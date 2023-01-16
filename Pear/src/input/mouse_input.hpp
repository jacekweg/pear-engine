#pragma once

#include "events/event.hpp"

namespace Pear
{
	/**
	 * @class MouseInput
	 * @brief A class to test mouse input event.
	 */
	class MouseInput
	{
	public:
		/**
		 * @brief The callback function for the mouse scroll event.
		 *
		 * @param data The event data.
		 * @return true if the event was handled and false otherwise.
		 */
		[[nodiscard]] static bool MouseScrolledCallback(EventData data);
	};
}
