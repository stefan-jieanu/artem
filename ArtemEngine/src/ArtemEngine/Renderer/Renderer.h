#pragma once

namespace ArtemEngine {

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return sRendererAPI_; }
	private:
		static RendererAPI sRendererAPI_;
		
	};
}

