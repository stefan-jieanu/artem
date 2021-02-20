#pragma once

#include "RendererAPI.h"

namespace ArtemEngine {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			sRendererAPI_->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			sRendererAPI_->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const Color& color)
		{
			sRendererAPI_->SetClearColor(color);
		}

		inline static void Clear()
		{
			sRendererAPI_->Clear();
		}

		inline static void DrawIndexed(const Shared<VertexArray>& vertexArray, uint32_t count)
		{
			sRendererAPI_->DrawIndexed(vertexArray, count);
		}
	private:
		static RendererAPI* sRendererAPI_;
	};

}