#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Toy {
	class TOY_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TOY_CORE_TRACE(...)    ::Toy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TOY_CORE_INFO(...)     ::Toy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TOY_CORE_WARN(...)     ::Toy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TOY_CORE_ERROR(...)    ::Toy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TOY_CORE_CRITICAL(...) ::Toy::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TOY_TRACE(...)         ::Toy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TOY_INFO(...)          ::Toy::Log::GetClientLogger()->info(__VA_ARGS__)
#define TOY_WARN(...)          ::Toy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TOY_ERROR(...)         ::Toy::Log::GetClientLogger()->error(__VA_ARGS__)
#define TOY_CRITICAL(...)      ::Toy::Log::GetClientLogger()->critical(__VA_ARGS__)
