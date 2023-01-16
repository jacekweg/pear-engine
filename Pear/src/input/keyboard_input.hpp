#pragma once

#include "events/event.hpp"

namespace Pear
{
	/**
	 * @class KeyboardInput
	 * @brief A class to test keyboard input events.
	 */
	class KeyboardInput
	{
	public:
		/**
		 * @brief The callback function for the key press event.
		 *
		 * @param data The event data.
		 * @return true if the event was handled and false otherwise.
		 */
		[[nodiscard]] static bool KeyPressedCallback(EventData data);
		/**
		 * @brief The callback function for the key release event.
		 *
		 * @param data The event data.
		 * @return true if the event was handled and false otherwise.
		 */
		[[nodiscard]] static bool KeyReleasedCallback(EventData data);
	};
}