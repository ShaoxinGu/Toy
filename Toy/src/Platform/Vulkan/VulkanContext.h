#pragma once
#include "Toy/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Toy {

	class VulkanContext : public RendererContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}