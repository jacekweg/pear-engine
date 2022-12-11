#pragma once
#include "pch.hpp"

#include "event.hpp"

namespace Pear
{
	enum class EventType
	{
		KeyPressed, KeyHeld, KeyReleased, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseWheelScrolled,
		WindowResized, WindowClosed, WindowOutOfFocus, WindowNowInFocus, WindowPositionChanged,
		Size
	};

	class EventController
	{
	public:
		template <typename I, typename F>
		static bool SubscribeToEvent(const EventType type, I* instance, const F& callback, const std::string& name)
		{
			const Event::Func& new_callback = std::bind(callback, instance, std::placeholders::_1);
			return SubscribeToEvent(type, new_callback, name);
		}
		static bool SubscribeToEvent(EventType type, const Event::Func& callback, const std::string& name);
		static bool UnsubscribeFromEvent(EventType type, const std::string& name);
		static bool FireEvent(EventType type, EventData data);
	private:
		static std::ranges::borrowed_iterator_t<std::vector<std::unique_ptr<Event>>&> FindEventByName(EventType type, const std::string& event_name);
	private:
		static std::array<std::vector<std::unique_ptr<Event>>, static_cast<int>(EventType::Size)> event_entries;
	};
}

