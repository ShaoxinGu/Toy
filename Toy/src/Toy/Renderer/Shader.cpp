#include "toypch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/Vulkan/VulkanShader.h"

namespace Toy {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			TOY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		case RendererAPI::API::Vulkan:
			return new VulkanShader(vertexSrc, fragmentSrc);
		}

		TOY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}