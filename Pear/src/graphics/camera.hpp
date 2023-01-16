#pragma once

#include "controller.hpp"

namespace Pear
{
	/**
	 * @class Camera
	 * @brief The Camera class simulating camera in the Pear engine.
	 */
	class Camera
	{
	public:
		/**
		 * @brief Constructs a new Camera object.
		 * @param aspect_ratio The aspect ratio of the camera.
		 */
		explicit Camera(float aspect_ratio = 
			static_cast<float>(Controller::GetInstance().GetWindow().GetWidth()) /
			static_cast<float>(Controller::GetInstance().GetWindow().GetHeight())
		);
		/**
		 * @brief Destroys the Camera object.
		 */
		~Camera();

		// Deleted copy and move constructors and assignment operators
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(Camera&&) = delete;

		/**
		 * @brief Updates the Camera object.
		 */
		void OnUpdate();

		/**
		 * @brief Sets the projection of the Camera object.
		 * @param left The left value of the projection.
		 * @param right The right value of the projection.
		 * @param bottom The bottom value of the projection.
		 * @param top The top value of the projection.
		 */
		void SetProjection(float left, float right, float bottom, float top);

		/**
		 * @brief Callback function for when a key is pressed.
		 * @param data The EventData associated with the event.
		 * @return Whether or not the event was handled.
		 */
		bool OnKeyPressedCallback(EventData data);
		/**
		 * @brief Callback function for when a key is released.
		 * @param data The EventData associated with the event.
		 * @return Whether or not the event was handled.
		 */
		bool OnKeyReleasedCallback(EventData data);

		/**
		 * @brief Callback function for when the mouse is scrolled.
		 * @param data The EventData associated with the event.
		 * @return Whether or not the event was handled.
		 */
		bool OnMouseScrolledCallback(EventData data);
		/**
		 * @brief Callback function for when the window is resized.
		 * @param data The EventData associated with the event.
		 * @return Whether or not the event was handled.
		 */
		bool OnWindowResizedCallback(EventData data);

		/**
		 * @brief Get the time step of the camera.
		 * @return The time step of the camera.
		 */
		[[nodiscard]] float GetTimeStep() const { return this->time_step; }
		/**
		 * @brief Set the time step of the camera.
		 * @param new_time_step The new time step of the camera.
		 */
		void SetTimeStep(const float new_time_step) { this->time_step = new_time_step; }

		/**
		 * @brief Get the maximum zoom of the camera.
		 * @return The maximum zoom of the camera.
		 */
		[[nodiscard]] float GetMaxZoom() const { return this->max_zoom; }
		/**
		 * @brief Set the maximum zoom of the camera.
		 * @param new_max_zoom The new maximum zoom of the camera.
		 */
		void SetMaxZoom(const float new_max_zoom) { this->max_zoom = new_max_zoom; }

		/**
		 * @brief Get the minimum zoom of the camera.
		 * @return The minimum zoom of the camera.
		 */
		[[nodiscard]] float GetMinZoom() const { return this->min_zoom; }
		/**
		 * @brief Set the minimum zoom of the camera.
		 * @param new_min_zoom The new minimum zoom of the camera.
		 */
		void SetMinZoom(const float new_min_zoom) { this->min_zoom = new_min_zoom; }

		/**
		 * @brief Get whether the camera is controllable or not.
		 * @return Whether the camera is controllable or not.
		 */
		[[nodiscard]] bool GetIsControllable() const { return this->is_controllable; }
		/**
		 * @brief Set whether the camera is controllable or not.
		 * @param new_is_controllable The new value for whether the camera is controllable or not.
		 */
		void SetIsControllable(bool new_is_controllable);

		/**
		 * @brief Get the current position of the camera.
		 * @return The current position of the camera.
		 */
		[[nodiscard]] const glm::vec3& GetPosition() const { return this->position; }
		/**
		 * @brief Set the current position of the camera.
		 * @param new_position The new position of the camera.
		 */
		void SetPosition(const glm::vec3& new_position) { this->position = new_position; RecalculateViewMatrix(); }

		/**
		 * @brief Get the current rotation of the camera.
		 * @return The current rotation of the camera.
		 */
		[[nodiscard]] float GetRotation() const { return this->rotation; }
		/**
		 * @brief Set the current rotation of the camera.
		 * @param new_rotation The new rotation of the camera.
		 */
		void SetRotation(const float new_rotation) { this->rotation = new_rotation; RecalculateViewMatrix(); }

		/**
		 * @brief Get the projection matrix of the camera.
		 * @return The projection matrix of the camera.
		 */
		[[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return this->projection_matrix; }
		/**
		 * @brief Get the view matrix of the camera.
		 * @return The view matrix of the camera.
		 */
		[[nodiscard]] const glm::mat4& GetViewMatrix() const { return this->view_matrix; }
		/**
		 * @brief Get the view-projection matrix of the camera.
		 * @return The view-projection matrix of the camera.
		 */
		[[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return this->view_projection_matrix; }
	private:
		/**
		 * @brief Recalculates the view matrix of the camera based on its current position and rotation.
		 */
		void RecalculateViewMatrix();
	private:
		float aspect_ratio;
		float rotation = 0.0f;
		float zoom = 2.5f;
		float max_zoom = 30.0f;
		float min_zoom = 0.25f;

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
