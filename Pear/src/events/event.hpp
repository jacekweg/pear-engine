#pragma once
#include "pch.hpp"

namespace Pear
{
	/* Max 64 bits (maybe 128?) */
	union EventData
	{
		char c;
		char c8[8];
		unsigned char u8[8];

		int32_t i32[2];
		uint16_t u16[4];

		double d64;
		float f32[2];

		const char* c_str;

		bool b;
	};

	class Event
	{
	public:
		typedef std::function<bool(EventData)> Func;

		explicit Event(Func callback, std::string name)
		: event_name(std::move(name)), callback(std::move(callback)){}

		[[nodiscard]] bool Callback(const EventData data) const { return callback(data); }
		[[nodiscard]] Func& GetCallbackFunction() { return callback; }
		[[nodiscard]] const std::string& GetEventName() { return event_name; }

	private:
		std::string event_name;
		Func callback;
	};
}
