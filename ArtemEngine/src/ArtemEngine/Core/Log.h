#pragma once

#include "Core.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

// Undefine these spdlog defines as they are only necessary as a tweak before including the library
// No need to have them defined to clutter the rest of the program
#undef SPDLOG_ACTIVE_LEVEL
#undef SPDLOG_DEBUG_ON
#undef SPDLOG_TRACE_ON

namespace ArtemEngine {

	class Log
	{
	public:
		static void Init();

		inline static Shared<spdlog::logger>& GetCoreLogger() { return sCoreLogger_; }
		inline static Shared<spdlog::logger>& GetClientLogger() { return sClientLogger_; }

	private:
		static Shared<spdlog::logger> sCoreLogger_;
		static Shared<spdlog::logger> sClientLogger_;
 	};

}

// Core log macros
#define LOG_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::ArtemEngine::Log::GetCoreLogger(), __VA_ARGS__)
#define LOG_CORE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::ArtemEngine::Log::GetCoreLogger(), __VA_ARGS__)
#define LOG_CORE_INFO(...) SPDLOG_LOGGER_INFO(::ArtemEngine::Log::GetCoreLogger(), __VA_ARGS__)
#define LOG_CORE_WARN(...)  SPDLOG_LOGGER_WARN(::ArtemEngine::Log::GetCoreLogger(), __VA_ARGS__)
#define LOG_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::ArtemEngine::Log::GetCoreLogger(), __VA_ARGS__)


// Client log macros
#define LOG_TRACE(...) SPDLOG_LOGGER_TRACE(::ArtemEngine::Log::GetClientLogger(), __VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(::ArtemEngine::Log::GetClientLogger(), __VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_INFO(::ArtemEngine::Log::GetClientLogger(), __VA_ARGS__)
#define LOG_WARN(...)  SPDLOG_LOGGER_WARN(::ArtemEngine::Log::GetClientLogger(), __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(::ArtemEngine::Log::GetClientLogger(), __VA_ARGS__)

