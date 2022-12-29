#include "pch.hpp"
#include "utils/logging.hpp"

#include "camera.hpp"
#include "events/event_controller.hpp"

#include <GLFW/glfw3.h>

namespace Pear
{
	Camera::Camera(const float aspect_ratio)
		:aspect_ratio(aspect_ratio),
	     projection_matrix(glm::ortho(-aspect_ratio * this->zoom, aspect_ratio * this->zoom, -this->zoom, this->zoom, -1.0f, 1.0f)),
		 view_matrix(1.0f)
	{
		this->view_projection_matrix = this->projection_matrix * this->view_matrix;

		EventController::SubscribeToEvent(EventType::MouseWheelScrolled, this, &Camera::OnMouseScrolledCallback, "CamMouseScrolled");
		EventController::SubscribeToEvent(EventType::WindowResized, this, &Camera::OnWindowResizedCallback, "CamWindowResized");
	}

	Camera::~Camera()
	{
		EventController::UnsubscribeFromEvent(EventType::MouseWheelScrolled, "CamMouseScrolled");
		EventController::UnsubscribeFromEvent(EventType::WindowResized, "CamWindowResized");
	}

	bool Camera::OnKeyPressedCallback(const EventData data)
	{
		switch (data.i32[0])
		{
			case GLFW_KEY_W:
				this->move_up = true;
				break;
			case GLFW_KEY_S:
				this->move_down = true;
				break;
			case GLFW_KEY_A:
				this->move_left = true;
				break;
			case GLFW_KEY_D:
				this->move_right = true;
				break;
			default: 
				break;
		}

		return true;
	}

	bool Camera::OnKeyReleasedCallback(const EventData data)
	{
		switch (data.i32[0])
		{
		case GLFW_KEY_W:
			this->move_up = false;
			break;
		case GLFW_KEY_S:
			this->move_down = false;
			break;
		case GLFW_KEY_A:
			this->move_left = false;
			break;
		case GLFW_KEY_D:
			this->move_right = false;
			break;
		default:
			break;
		}

		return true;
	}

	bool Camera::OnMouseScrolledCallback(const EventData data)
	{
		const auto y_offset = static_cast<float>(data.d64);
		this->zoom -= y_offset * 0.25f;
		this->zoom = glm::max(this->zoom, this->min_zoom);
		this->zoom = glm::min(this->zoom, this->max_zoom);
		SetProjection(-this->aspect_ratio * this->zoom, this->aspect_ratio * this->zoom, -this->zoom, this->zoom);

		LOG("Camera zoom {}", zoom)
		return true;
	}

	bool Camera::OnWindowResizedCallback(const EventData data)
	{
		const int new_width = data.i32[0];
		const int new_height = data.i32[1];

		this->aspect_ratio = static_cast<float>(new_width) / static_cast<float>(new_height);
		SetProjection(-this->aspect_ratio * this->zoom, this->aspect_ratio * this->zoom, -this->zoom, this->zoom);

		return true;
	}

	void Camera::SetIsControllable(const bool new_is_controllable)
	{
		if (new_is_controllable)
		{
			EventController::SubscribeToEvent(EventType::KeyPressed, this, &Camera::OnKeyPressedCallback, "CamKeyPressed");
			EventController::SubscribeToEvent(EventType::KeyReleased, this, &Camera::OnKeyReleasedCallback, "CamKeyReleased");
		}
		else
		{
			EventController::UnsubscribeFromEvent(EventType::KeyPressed, "CamKeyPressed");
			EventController::UnsubscribeFromEvent(EventType::KeyReleased, "CamKeyReleased");
		}
		this->is_controllable = new_is_controllable;
	}

	void Camera::SetProjection(const float left, const float right, const float bottom, const float top)
	{
		this->projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		this->view_projection_matrix = this->projection_matrix * this->view_matrix;
	}

	void Camera::OnUpdate()
	{
		if (this->is_controllable)
		{
			if (this->move_up)
			{
				this->position.x += -sin(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
				this->position.y += cos(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
			}
			if (this->move_down)
			{
				this->position.x -= -sin(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
				this->position.y -= cos(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
			}
			if (this->move_left)
			{
				this->position.x -= cos(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
				this->position.y -= sin(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
			}
			if (this->move_right)
			{
				this->position.x += cos(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
				this->position.y += sin(glm::radians(this->rotation)) * this->transform_speed * this->time_step;
			}
		}
		RecalculateViewMatrix();
		this->view_projection_matrix = this->projection_matrix * this->view_matrix;
		this->transform_speed = this->zoom;
	}

	void Camera::RecalculateViewMatrix()
	{
		const glm::mat4 transform = translate(glm::mat4(1.0f), this->position)
		* rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0, 0, 1));

		this->view_matrix = inverse(transform);
		this->view_projection_matrix = this->projection_matrix * this->view_matrix;
	}
}
