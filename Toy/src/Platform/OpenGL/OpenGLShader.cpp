#include "toypch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace Toy {
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_RendererID(0)
	{
		unsigned int program = glCreateProgram();
		m_RendererID = program;

		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(id);

			TOY_CORE_ERROR(infoLog.data());
			TOY_CORE_ASSERT(false, "Shader compilation failure!")
				return 0;
		}
		return id;
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name) const
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
	}

}