#pragma once
#include "pch.hpp"

namespace Pear
{
	class Shader
	{
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(Shader&&) = delete;

		void Bind() const;
		void Unbind() const;

		void SetUniformFloat2(const glm::vec2& vec, const std::string& uniform_name) const;
		void SetUniformFloat3(const glm::vec3& vec, const std::string& uniform_name) const;
		void SetUniformFloat4(const glm::vec4& vec, const std::string& uniform_name) const;
		void SetUniformMat4(const glm::mat4& mat, const std::string& uniform_name) const;
		void SetUniformInt(int value, const std::string& uniform_name) const;
		void SetUniformFloat(float value, const std::string& uniform_name) const;

		[[nodiscard]] const std::string& GetName() const { return this->name; }
	private:
		static std::string ReadFile(const std::string& file_path);
	private:
		uint32_t render_id;
		std::string name;
	};
}
