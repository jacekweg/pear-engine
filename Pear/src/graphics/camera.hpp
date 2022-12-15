#pragma once

#include "controller.hpp"

namespace Pear
{
	class Camera
	{
	public:
		explicit Camera(float aspect_ratio = 
			static_cast<float>(Controller::GetInstance().GetWindow().GetWidth()) /
			static_cast<float>(Controller::GetInstance().GetWindow().GetHeight())
		);
		~Camera();

		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(Camera&&) = delete;

		void OnUpdate();

		void SetProjection(float left, float right, float bottom, float top);

		bool OnKeyPressedCallback(EventData data);
		bool OnKeyReleasedCallback(EventData data);
		bool OnMouseScrolledCallback(EventData data);
		bool OnWindowResizedCallback(EventData data);

		[[nodiscard]] float GetTimeStep() const { return this->time_step; }
		void SetTimeStep(const float new_time_step) { this->time_step = new_time_step; }

		[[nodiscard]] bool GetIsControllable() const { return this->is_controllable; }
		void SetIsControllable(bool new_is_controllable);

		[[nodiscard]] const glm::vec3& GetPosition() const { return this->position; }
		void SetPosition(const glm::vec3& new_position) { this->position = new_position; RecalculateViewMatrix(); }

		[[nodiscard]] float GetRotation() const { return this->rotation; }
		void SetRotation(const float new_rotation) { this->rotation = new_rotation; RecalculateViewMatrix(); }

		[[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return this->projection_matrix; }
		[[nodiscard]] const glm::mat4& GetViewMatrix() const { return this->view_matrix; }
		[[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return this->view_projection_matrix; }
	private:
		void RecalculateViewMatrix();
	private:
		float aspect_ratio;
		float rotation = 0.0f;
		float zoom = 2.5f; // was 1.0f

		float time_step = 0.0f;

		float transform_speed = 2.0f;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };

		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 view_projection_matrix{};

		bool move_up{}, move_down{}, move_left{}, move_right{};
		bool is_controllable{};
	};
}
