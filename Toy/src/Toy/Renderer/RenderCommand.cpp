#include "toypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Toy {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}