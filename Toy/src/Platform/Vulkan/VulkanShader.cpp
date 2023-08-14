#include "toypch.h"
#include "VulkanShader.h"

namespace Toy {

	VulkanShader::VulkanShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{

	}

	VulkanShader::~VulkanShader()
	{

	}

	void VulkanShader::Bind() const
	{

	}

	void VulkanShader::Unbind() const
	{

	}

	void VulkanShader::UploadUniformInt(const std::string& name, int value)
	{

	}

	void VulkanShader::UploadUniformFloat(const std::string& name, float value)
	{

	}

	void VulkanShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{

	}

	void VulkanShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{

	}

	void VulkanShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{

	}

	void VulkanShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{

	}

	void VulkanShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{

	}

	unsigned int VulkanShader::CompileShader(unsigned int type, const std::string& source)
	{
		return 0;
	}

	int VulkanShader::GetUniformLocation(const std::string& name) const
	{
		return 0;
	}

}