#pragma once

namespace ArtemEngine {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;

		static Shared<Texture> Create(const std::string& filepath);
		static Shared<Texture> Create(uint32_t width, uint32_t height);
	};

}