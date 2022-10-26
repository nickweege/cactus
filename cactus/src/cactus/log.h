#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "core.h"

namespace cactus {

	class log {
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; }
		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};
}

// Core log macros
#define CACTUS_CORE_TRACE(...)    ::cactus::log::get_core_logger()->trace(__VA_ARGS__)
#define CACTUS_CORE_INFO(...)     ::cactus::log::get_core_logger()->info(__VA_ARGS__)
#define CACTUS_CORE_WARN(...)     ::cactus::log::get_core_logger()->warn(__VA_ARGS__)
#define CACTUS_CORE_ERROR(...)    ::cactus::log::get_core_logger()->error(__VA_ARGS__)
#define CACTUS_CORE_FATAL(...)    ::cactus::log::get_core_logger()->fatal(__VA_ARGS__)

// Client log macros
#define CACTUS_TRACE(...)         ::cactus::log::get_client_logger()->trace(__VA_ARGS__)
#define CACTUS_INFO(...)          ::cactus::log::get_client_logger()->info(__VA_ARGS__)
#define CACTUS_WARN(...)          ::cactus::log::get_client_logger()->warn(__VA_ARGS__)
#define CACTUS_ERROR(...)         ::cactus::log::get_client_logger()->error(__VA_ARGS__)
#define CACTUS_FATAL(...)         ::cactus::log::get_client_logger()->fatal(__VA_ARGS__)