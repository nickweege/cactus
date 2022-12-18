#pragma once

#ifdef CACTUS_WINDOWS_PLATFORM
#endif

#ifdef CACTUS_ENABLE_ASSERTS
	#define CACTUS_ASSERT(x, ...) { (if(!x)) { CACTUS_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CACTUS_CORE_ASSERT(x, ...) { (if(!x)) { CACTUS_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CACTUS_ASSERT(x, ...)
	#define CACTUS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (x << 1)

#define CACTUS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)