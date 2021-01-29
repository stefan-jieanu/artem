#pragma once

#include <memory>
#include "ArtemEngine/Renderer/Buffers.h"

namespace ArtemEngine {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}