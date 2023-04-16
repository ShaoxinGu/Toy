#include "toypch.h"
#include "Shader.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace Toy {
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

    void Shader::UploadUniform1i(const std::string& name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::UploadUniform1f(const std::string& name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::UploadUniform1iv(const std::string& name, int count, int* value)
    {
        glUniform1iv(GetUniformLocation(name), count, value);
    }

    void Shader::UploadUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    int Shader::GetUniformLocation(const std::string& name) const
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