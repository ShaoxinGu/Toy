#include "toypch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/Vulkan/VulkanBuffer.h"

namespace Toy {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            TOY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::API::Vulkan:
			return new VulkanVertexBuffer(vertices, size);
        }

        TOY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            TOY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::API::Vulkan:
			return new VulkanIndexBuffer(indices, count);
        }

        TOY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}