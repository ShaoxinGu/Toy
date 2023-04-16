#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Toy {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniform1i(const std::string& name, int value);
		void UploadUniform1f(const std::string& name, float value);
		void UploadUniform1iv(const std::string& name, int count, int* value);
		void UploadUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int CompileShader(unsigned int type, const std::string& source);
		int GetUniformLocation(const std::string& name) const;
	private:
		uint32_t m_RendererID;
		mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	};

}