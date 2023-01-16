#pragma once

#include <imconfig.h>

namespace Pear
{
	/**
	 * @class ImGuiInstance
	 * @brief A class to handle ImGui related functionality.
	 */
	class ImGuiInstance
	{
	public:
		/**
		 * @brief Begins rendering ImGui.
		 */
		static void BeginRender();
		/**
		 * @brief Ends rendering ImGui.
		 */
		static void EndRender();

		/**
		 * @brief Begins ImGui frame.
		 */
		static void BeginFrame();
		/**
		 * @brief Renders ImGui window.
		 * @param time_step The time step of the current frame.
		 */
		static void RenderWindow(float time_step);
		/**
		 * @brief Ends ImGui frame.
		 */
		static void EndFrame();

		/**
		 * @brief Updates ImGui windows.
		 * @param time_step The time step of the current frame.
		 */
		static void OnUpdate(float time_step);
	};

}
