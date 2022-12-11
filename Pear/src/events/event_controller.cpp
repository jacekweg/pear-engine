#include "pch.hpp"
#include "event_controller.hpp"

namespace Pear
{
	std::array<std::vector<std::unique_ptr<Event>>, static_cast<int>(EventType::Size)> EventController::event_entries = {};

	bool EventController::SubscribeToEvent(EventType type, const Event::Func& callback, const std::string& name)
	{
		auto new_event = std::make_unique<Event>(callback, name);
		auto& events = event_entries[static_cast<int>(type)];

		if(const auto it = FindEventByName(type, name);
		   it != events.end())
		{
			return false;
		}

		events.emplace_back(std::move(new_event));
		return true;
	}

	bool EventController::UnsubscribeFromEvent(EventType type, const std::string& name)
	{
		auto& events = event_entries[static_cast<int>(type)];

		if (const auto it = FindEventByName(type, name);
			it != events.end())
		{
			std::unique_ptr<Event> removed_event = std::move(*it);
			events.erase(it);
			return true;
		}

		return false;
	}

	bool EventController::FireEvent(EventType type, const EventData data)
	{
		const auto& events = event_entries[static_cast<int>(type)];

		if(events.empty())
		{
			return false;
		}

		if (std::ranges::all_of(events.cbegin(), events.cend(), [&data](auto& e) { return e->Callback(data); }))
		{
			return true;
		}

		return false;
	}

	std::ranges::borrowed_iterator_t<std::vector<std::unique_ptr<Event>>&> EventController::FindEventByName(EventType type, const std::string& event_name)
	{
		auto& events = event_entries[static_cast<int>(type)];
		return std::ranges::find_if(events, [&](const std::unique_ptr<Event>& obj){ return obj->GetEventName() == event_name; });
	}
}
