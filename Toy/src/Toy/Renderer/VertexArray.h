#pragma once

#include <memory>
#include "Toy/Renderer/Buffer.h"

namespace Toy {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>> & GetVertexBuffers() = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() = 0;

		static VertexArray* Create();
	};

}