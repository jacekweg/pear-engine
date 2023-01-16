#pragma once
#include "pch.hpp"

#include "event.hpp"

namespace Pear
{
	/**
	 * @enum class EventType
	 * @brief Enumeration of supported event types in the Pear engine.
	 */
	enum class EventType
	{
		KeyPressed, KeyHeld, KeyReleased, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseWheelScrolled,
		WindowResized, WindowClosed, WindowOutOfFocus, WindowNowInFocus, WindowPositionChanged,
		Size
	};

	/**
	 * @class EventController
	 * @brief The EventController class for handling events in the Pear engine.
	 */
	class EventController
	{
	public:
		/**
		 * @brief Subscribes the specified instance and callback function to the specified event type.
		 * @tparam I The type of the instance.
		 * @tparam F The type of the callback function.
		 *
		 * @param type The event type to subscribe to.
		 * @param instance The instance to be passed to the callback function.
		 * @param callback The callback function to be called when the event is fired.
		 * @param name The name of the event.
		 *
		 * @return true if the subscription was successful, false otherwise.
		 */
		template <typename I, typename F>
		static bool SubscribeToEvent(const EventType type, I* instance, const F& callback, const std::string& name)
		{
			const Event::Func& new_callback = std::bind(callback, instance, std::placeholders::_1);
			return SubscribeToEvent(type, new_callback, name);
		}
		/**
		 * @brief Subscribes the specified callback function to the specified event type.
		 *
		 * @param type The event type to subscribe to.
		 * @param callback The callback function to be called when the event is fired.
		 * @param name The name of the event.
		 *
		 * @return true if the subscription was successful, false otherwise.
		 */
		static bool SubscribeToEvent(EventType type, const Event::Func& callback, const std::string& name);
		/**
		 * @brief Unsubscribes the specified event with the specified name from the specified event type.
		 *
		 * @param type The event type to unsubscribe from.
		 * @param name The name of the event.
		 *
		 * @return true if the unsubscription was successful, false otherwise.
		 */
		static bool UnsubscribeFromEvent(EventType type, const std::string& name);
		/**
		 * @brief Fires the specified event with the specified data.
		 *
		 * @param type The event type to fire.
		 * @param data The data to be passed to the event's callback function.
		 *
		 * @return true if the event was handled correctly, false otherwise.
		 */
		static bool FireEvent(EventType type, EventData data);
	private:
		/**
		 * @brief Finds the event with the specified name from the specified event type.
		 *
		 * @param type The event type to search in.
		 * @param event_name identifier of the event
		 */
		static std::ranges::borrowed_iterator_t<std::vector<std::unique_ptr<Event>>&> FindEventByName(EventType type, const std::string& event_name);
	private:
		/**
		 * @brief An array of vectors of unique pointers to events, indexed by the EventType enum.
		 */
		static std::array<std::vector<std::unique_ptr<Event>>, static_cast<int>(EventType::Size)> event_entries;
	};
}
