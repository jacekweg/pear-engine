#pragma once
#include "pch.hpp"

namespace Pear
{
	/**
	 * @union EventData
	 * @brief The union representing data of an event (max 64 bits).
	 */
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

	/**
	 * @class Event
	 * @brief The Event class for handling events in the Pear engine.
	 */
	class Event
	{
	public:
		/**
		 * @typedef Func
		 * @brief A function type for event callbacks.
		 */
		typedef std::function<bool(EventData)> Func;

		/**
		 * @brief Constructs a new Event object with the specified callback function and name.
		 * @param callback The callback function to be used for this event.
		 * @param name The name of the event.
		 */
		explicit Event(Func callback, std::string name)
		: function_id(std::move(name)), callback(std::move(callback)){}

		/**
		 * @brief Calls the callback function for this event with the specified data.
		 * @param data The data to be passed to the callback function.
		 * @return The return value of the callback function.
		 */
		[[nodiscard]] bool Callback(const EventData data) const { return callback(data); }

		/**
		 * @brief Gets the callback function for this event.
		 * @return The callback function.
		 */
		[[nodiscard]] Func& GetCallbackFunction() { return callback; }

		/**
		 * @brief Gets the identifier of the function.
		 * @return The identifier of the function.
		 */
		[[nodiscard]] const std::string& GetIdentifierName() { return function_id; }

	private:
		std::string function_id;
		Func callback;
	};
}
