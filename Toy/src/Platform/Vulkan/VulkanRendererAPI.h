#pragma once

#include "Toy/Renderer/RendererAPI.h"

namespace Toy {

	class VulkanRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

}