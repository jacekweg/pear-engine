#include "pch.hpp"
#include "utils/logging.hpp"

#include "window.hpp"
#include "controller.hpp"
#include "events/event_controller.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pear
{
	Window::Window(std::string name, const int width, const int height)
		:name(std::move(name)), width(width), height(height), pos_x(0), pos_y(0), instance(nullptr), monitor(nullptr)
	{
        const int glfw_status = glfwInit();
        ASSERT(glfw_status, "glfw wasn't initialized")
        if(!glfw_status)
        {
	        return;
        }

        /* Create a windowed mode window and its OpenGL context */
        this->instance = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
        ASSERT(this->instance, "window wasn't created")
        if (!this->instance)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(this->instance);

        glfwSetWindowUserPointer(this->instance, this);

        this->monitor = glfwGetPrimaryMonitor();
        glfwGetWindowPos(this->instance, &this->pos_x, &this->pos_y);

        const int glad_status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        ASSERT(glad_status, "glad wasn't initialized")

        glfwSetWindowSizeCallback(this->instance, SetWindowSizeCallback);
        glfwSetWindowCloseCallback(this->instance, SetWindowCloseCallback);
        glfwSetWindowPosCallback(this->instance, SetWindowPositionCallback);
        glfwSetKeyCallback(this->instance, SetKeyCallback);
        glfwSetScrollCallback(this->instance, SetScrollCallback);

        EventController::SubscribeToEvent(EventType::WindowResized, this, &Window::WindowResizeCallback, "WindowResized");
        EventController::SubscribeToEvent(EventType::WindowClosed, this, &Window::WindowCloseCallback, "WindowClosed");

        LOG("Created window with name: {2:}, width: {0:}px, height: {1:}px\n", this->width, this->height, this->name)
	}

	Window::~Window()
	{
        EventController::UnsubscribeFromEvent(EventType::WindowResized, "WindowResized");
        EventController::UnsubscribeFromEvent(EventType::WindowClosed, "WindowClosed");
        glfwTerminate();
	}

	void Window::OnUpdate() const
	{
        /* Swap front and back buffers */
        glfwSwapBuffers(this->instance);

        /* Poll for and process events */
        glfwPollEvents();
	}

    void Window::MakeFullscreen(const bool fullscreen)
    {
	   if(IsFullscreen() == fullscreen)
			return;

	   if(fullscreen)
	   {
           glfwGetWindowPos(this->instance, &this->pos_x, &this->pos_y);
           glfwGetWindowSize(this->instance, &this->width, &this->height);
           const GLFWvidmode* mode = glfwGetVideoMode(this->monitor);
           glfwSetWindowMonitor(this->instance, this->monitor, 0, 0, mode->width, mode->height, 0);
	   }
	   else
	   {
           glfwSetWindowMonitor(this->instance, nullptr, this->pos_x, this->pos_y, this->width, this->height, 0);
	   }
	}

    bool Window::IsFullscreen() const
    {
        return glfwGetWindowMonitor(this->instance) != nullptr;
    }

    void Window::SetWindowSizeCallback([[maybe_unused]] GLFWwindow* window, const int new_width, const int new_height)
	{
		EventController::FireEvent(EventType::WindowResized, { .i32 = {new_width, new_height} });
	}

	void Window::SetWindowCloseCallback([[maybe_unused]] GLFWwindow* window)
	{
        EventController::FireEvent(EventType::WindowClosed, { .b = true });
	}

	void Window::SetKeyCallback([[maybe_unused]] GLFWwindow* window, const int key, const int scancode, const int action, [[maybe_unused]] int mods)
	{
        switch (action)
        {
			case GLFW_PRESS:
	            EventController::FireEvent(EventType::KeyPressed, { .i32 = {key} });
	            break;
			case GLFW_REPEAT:
	            EventController::FireEvent(EventType::KeyHeld, { .i32 = {key} });
	            break;
			case GLFW_RELEASE:
	            EventController::FireEvent(EventType::KeyReleased, { .i32 = {key} });
	            break;
			default:
                break;
        }
	}

    void Window::SetScrollCallback([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] const double x_offset, double y_offset)
    {
        EventController::FireEvent(EventType::MouseWheelScrolled, { .d64 = y_offset });
    }

    void Window::SetWindowPositionCallback([[maybe_unused]] GLFWwindow* window, const int x_pos, const int y_pos)
    {
        EventController::FireEvent(EventType::WindowPositionChanged, { .i32 = {x_pos, y_pos} });
    }

    bool Window::WindowResizeCallback(const EventData data)
	{
        if (!this->IsFullscreen())
        {
            const int new_width = data.i32[0];
            const int new_height = data.i32[1];
            this->width = new_width;
            this->height = new_height;
            LOG("Window resized width: {}px height: {}px", this->width, this->height)
        }
        return true;
	}

    bool Window::WindowCloseCallback(const EventData data) const
    {
        const bool window_close = data.b;
        if (window_close)
        {
            glfwDestroyWindow(this->instance);
            Controller::GetInstance().Stop();
        }
        return window_close;
	}

    void Window::SetSize(const int new_width, const int new_height) const
    {
        glfwSetWindowSize(this->instance, new_width, new_height);
    }

    void Window::SetName(const std::string& new_name)
    {
        glfwSetWindowTitle(this->instance, new_name.c_str());
        this->name = new_name;
    }
}
