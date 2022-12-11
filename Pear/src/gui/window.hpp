#pragma once
#include "pch.hpp"

#include "events/event.hpp"

#include <GLFW/glfw3.h>

namespace Pear
{
	class Window
	{
	public:
		explicit Window(std::string name, int width, int height);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		void OnUpdate() const;

		void MakeFullscreen(bool fullscreen);
		[[nodiscard]] bool IsFullscreen() const;

		bool WindowResizeCallback(EventData data);
		[[nodiscard]] bool WindowCloseCallback(EventData data) const;

		[[nodiscard]] int GetWidth() const { return width; }
		[[nodiscard]] int GetHeight() const { return height; }

		void SetSize(int new_width, int new_height) const;
		void SetName(const std::string& new_name);

		[[nodiscard]] GLFWwindow* GetInstance() const { return instance; }
		[[nodiscard]] bool IsFocused() const { return glfwGetWindowAttrib(instance, GLFW_FOCUSED);}
 	private:
		static void SetWindowSizeCallback(GLFWwindow* window, int new_width, int new_height);
		static void SetWindowCloseCallback(GLFWwindow* window);
		static void SetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void SetScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
		static void SetWindowPositionCallback(GLFWwindow* window, int x_pos, int y_pos);
	private:
		std::string name;
		int width, height;
		int pos_x, pos_y;
		GLFWwindow* instance;
		GLFWmonitor* monitor;
	};
}
