#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace ArtemEngine {

	class ARTEM_ENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger_; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger_; }

	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger_;
		static std::shared_ptr<spdlog::logger> sClientLogger_;
 	};

}

// Core log macros
#define LOG_CORE_TRACE(...) ::ArtemEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) ::ArtemEngine::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define LOG_CORE_INFO(...)  ::ArtemEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)  ::ArtemEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::ArtemEngine::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define LOG_TRACE(...) ::ArtemEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::ArtemEngine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)  ::ArtemEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::ArtemEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::ArtemEngine::Log::GetClientLogger()->error(__VA_ARGS__)

