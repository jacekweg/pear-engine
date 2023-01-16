#pragma once
#include "pch.hpp"

#include "events/event.hpp"

#include <GLFW/glfw3.h>

namespace Pear
{
	/**
	 * @class Window
	 * @brief A class for creating and managing a GLFW window.
	 */
	class Window
	{
	public:
		/**
		 * @brief Constructs a new Window object.
		 * @param name The name of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 */
		explicit Window(std::string name, int width, int height);
		/**
		 * @brief Destroys the Window object.
		 */
		~Window();

		// Deleted copy and move constructors and assignment operators
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		/**
		 * @brief Updates the window.
		 */
		void OnUpdate() const;

		/**
		 * @brief Makes the window fullscreen.
		 * @param fullscreen Whether the window should be fullscreen.
		 */
		void MakeFullscreen(bool fullscreen);
		/**
		 * @brief Checks if the window is fullscreen.
		 * @return true if the window is fullscreen.
		 * @return false if the window is not fullscreen.
		 */
		[[nodiscard]] bool IsFullscreen() const;

		/**
		 * @brief Callback function for handling window resize events.
		 * @param data Event data.
		 * @return true if the event was handled and false otherwise.
		 */
		bool WindowResizeCallback(EventData data);
		/**
		 * @brief Callback function for handling window close events.
		 * @param data Event data.
		 * @return true if the event was handled and false otherwise.
		 */
		[[nodiscard]] bool WindowCloseCallback(EventData data) const;

		/**
		 * @brief Gets the width of the window.
		 * @return The width of the window.
		 */
		[[nodiscard]] int GetWidth() const { return width; }
		/**
		 * @brief Gets the height of the window.
		 * @return The height of the window.
		 */
		[[nodiscard]] int GetHeight() const { return height; }

		/**
		 * @brief Sets the size of the window.
		 * @param new_width The new width of the window.
		 * @param new_height The new height of the window.
		 */
		void SetSize(int new_width, int new_height) const;
		/**
		 * @brief Sets the name of the window.
		 * @param new_name The new name of the window.
		 */
		void SetName(const std::string& new_name);

		/**
		 * @brief Gets the GLFW window instance.
		 * @return The GLFW window instance.
		 */
		[[nodiscard]] GLFWwindow* GetInstance() const { return instance; }
		/**
		 * @brief Checks if the window is focused.
		 * @return true if the window is focused, and false otherwise.
		 */
		[[nodiscard]] bool IsFocused() const { return glfwGetWindowAttrib(instance, GLFW_FOCUSED);}
 	private:
		/**
		 * @brief Callback function for handling window size changes.
		 * @param window The GLFW window instance.
		 * @param new_width The new width of the window.
		 * @param new_height The new height of the window.
		 */
		static void SetWindowSizeCallback(GLFWwindow* window, int new_width, int new_height);
		/**
		 * @brief Callback function for handling window close events.
		 * @param window The GLFW window instance.
		 */
		static void SetWindowCloseCallback(GLFWwindow* window);
		/**
		 * @brief Callback function for handling keyboard events.
		 * @param window The GLFW window instance.
		 * @param key The pressed key.
		 * @param scancode The scancode of the key.
		 * @param action The action of the key (pressed, released, repeated).
		 * @param mods Bit field describing which modifiers keys were held down.
		 */
		static void SetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		/**
		 * @brief Callback function for handling mouse scroll events.
		 * @param window The GLFW window instance.
		 * @param x_offset The scroll offset along the x-axis.
		 * @param y_offset The scroll offset along the y-axis.
		 */
		static void SetScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
		/**
		 * @brief Callback function for handling window position changes.
		 * @param window The GLFW window instance.
		 * @param x_pos The new x-coordinate of the window's position.
		 * @param y_pos The new y-coordinate of the window's position.
		 */
		static void SetWindowPositionCallback(GLFWwindow* window, int x_pos, int y_pos);
	private:
		std::string name;
		int width, height;
		int pos_x, pos_y;
		GLFWwindow* instance;
		GLFWmonitor* monitor;
	};
}
