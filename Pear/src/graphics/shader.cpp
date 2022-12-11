#include "pch.hpp"
#include "utils/logging.hpp"

#include "shader.hpp"

#include <glad/glad.h>

namespace Pear
{
	Shader::Shader(const std::string& vertex_src, const std::string& fragment_src)
	{
		const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		const std::string vertex_shader_str = ReadFile(vertex_src);
		const std::string fragment_shader_str = ReadFile(fragment_src);

		const char* vertex_shader_src = vertex_shader_str.c_str();
		const char* fragment_shader_src = fragment_shader_str.c_str();

		GLint result = 0;
		int log_length;

		/* Compile vertex shader */
		
		glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
		glCompileShader(vertex_shader);

		/* Check vertex shader */

		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
		std::vector<GLchar> vertex_shader_error(log_length > 1 ? log_length : 1);
		glGetShaderInfoLog(vertex_shader, log_length, nullptr, &vertex_shader_error[0]);

		if (vertex_shader_error.size() > 1)
		{
			LOG("{}", vertex_shader_error.data())
		}

		/* Compile fragment shader */

		glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);
		glCompileShader(fragment_shader);

		/* Check fragment shader */

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
		std::vector<GLchar> fragment_shader_error(log_length > 1 ? log_length : 1);
		glGetShaderInfoLog(fragment_shader, log_length, nullptr, &fragment_shader_error[0]);

		if (fragment_shader_error.size() > 1)
		{
			LOG("{}", fragment_shader_error.data())
		}

		/* Linking program */

		const GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &result);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
		std::vector<GLchar> program_error(log_length > 1 ? log_length : 1);
		glGetProgramInfoLog(program, log_length, nullptr, &program_error[0]);

		if (program_error.size() > 1)
		{
			LOG("{}", program_error.data())
		}

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		this->render_id = program;
	}

	Shader::~Shader()
	{
		ASSERT(this->render_id, "Program was deleted earlier")
		glDeleteProgram(this->render_id);
	}

	std::string Shader::ReadFile(const std::string& file_path)
	{
		std::string content;
		std::ifstream file_stream(file_path, std::ios::in);

		if (!file_stream.is_open())
		{
			LOG("Could not open file {}", file_path)
				file_stream.close();
			return {};
		}

		std::string line;
		while (!file_stream.eof())
		{
			std::getline(file_stream, line);
			content.append(line + '\n');
		}

		file_stream.close();
		return content;
	}

	void Shader::Bind() const
	{
		ASSERT(this, "Shader has to be created first")
		glUseProgram(this->render_id);
	}

	void Shader::Unbind() const
	{
		ASSERT(this->render_id, "Program wasn't bound")
		glUseProgram(0);
	}

	void Shader::SetUniformFloat2(const glm::vec2& vec, const std::string& uniform_name) const
	{
		const GLint location = glGetUniformLocation(this->render_id, uniform_name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void Shader::SetUniformFloat3(const glm::vec3& vec, const std::string& uniform_name) const
	{
		const GLint location = glGetUniformLocation(this->render_id, uniform_name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void Shader::SetUniformFloat4(const glm::vec4& vec, const std::string& uniform_name) const
	{
		const GLint location = glGetUniformLocation(this->render_id, uniform_name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::SetUniformMat4(const glm::mat4& mat, const std::string& uniform_name) const
	{
		const GLint location = glGetUniformLocation(this->render_id, uniform_name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(mat));
	}

	void Shader::SetUniformInt(const int value, const std::string& uniform_name) const
	{
		const GLint location = glGetUniformLocation(this->render_id, uniform_name.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetUniformFloat(const float value, const std::string& uniform_name) const
	{
		const GLint location = glGetUniformLocation(this->render_id, uniform_name.c_str());
		glUniform1f(location, value);
	}
}
