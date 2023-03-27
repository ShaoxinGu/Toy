#include "toypch.h"
#include "Toy/Renderer/VertexArray.h"

#include "Toy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Toy {
	
	VertexArray* VertexArray::Create()
	{

        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            TOY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
        }

        TOY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
	}

}