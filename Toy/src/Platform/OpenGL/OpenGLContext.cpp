#include "toypch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#define SPDLOG_FMT_EXTERNAL 
namespace Toy {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TOY_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TOY_CORE_ASSERT(status, "Failed to initialize Glad!");

		TOY_CORE_INFO("OpenGL renderer: {0}", (const char*)glGetString(GL_RENDERER));
		TOY_CORE_INFO("OpenGL vendor: {0}", (const char*)glGetString(GL_VENDOR));
		TOY_CORE_INFO("OpenGL version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}