#pragma once
#include "pch.hpp"

namespace Pear
{
	/**
	 * @class Shader
	 * @brief A class representing a GPU program made up of a vertex and fragment shaders.
	 */
	class Shader
	{
	public:
		/**
		 * @brief Constructs a Shader object.
		 * @param vertex_src The source code of the vertex shader.
		 * @param fragment_src The source code of the fragment shader.
		 */
		Shader(const std::string& vertex_src, const std::string& fragment_src);

		/**
		 * @brief Destructor for the Shader class.
		 */
		~Shader();

		// Deleted copy and move constructors and assignment operators
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(Shader&&) = delete;

		/**
		 * @brief Binds the shader program.
		 */
		void Bind() const;
		/**
		 * @brief Unbinds the shader program.
		 */
		void Unbind() const;

		/**
		 * @brief Sets the uniform value of a float2 vector.
		 * @param vec The float2 vector.
		 * @param uniform_name The name of the uniform variable.
		 */
		void SetUniformFloat2(const glm::vec2& vec, const std::string& uniform_name) const;
		/**
		 * @brief Sets the uniform value of a float3 vector.
		 * @param vec The float3 vector.
		 * @param uniform_name The name of the uniform variable.
		 */
		void SetUniformFloat3(const glm::vec3& vec, const std::string& uniform_name) const;
		/**
		 * @brief Sets the uniform value of a float4 vector.
		 * @param vec The float4 vector.
		 * @param uniform_name The name of the uniform variable.
		 */
		void SetUniformFloat4(const glm::vec4& vec, const std::string& uniform_name) const;
		/**
		 * @brief Sets the uniform value of a 4x4 matrix.
		 * @param mat The 4x4 matrix.
		 * @param uniform_name The name of the uniform variable
		 */
		void SetUniformMat4(const glm::mat4& mat, const std::string& uniform_name) const;
		/**
		 * @brief Sets the uniform value of an integer.
		 * @param value The integer value.
		 * @param uniform_name The name of the uniform variable.
		 */
		void SetUniformInt(int value, const std::string& uniform_name) const;
		/**
		 * @brief Sets the uniform value of a float.
		 * @param value The float value.
		 * @param uniform_name The name of the uniform variable.
		 */
		void SetUniformFloat(float value, const std::string& uniform_name) const;

		/**
		 * @brief Gets the name of the shader program.
		 * @return The name of the shader program.
		 */
		[[nodiscard]] const std::string& GetName() const { return this->name; }
	private:
		/**
		 * @brief Reads the content of a file and returns it as a string.
		 * @param file_path The path of the file to read.
		 * @return The content of the file as a string.
		 */
		static std::string ReadFile(const std::string& file_path);
	private:
		uint32_t render_id;
		std::string name;
	};
}
