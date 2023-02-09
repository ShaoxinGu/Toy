#pragma once

#ifdef TOY_PLATFORM_WINDOWS
	#if TOY_DYNAMIC_LINK
		#if TOY_BUILD_DLL
			#define TOY_API __declspec(dllexport)
		#else
			#define TOY_API __declspec(dllimport)
		#endif // TOY_BUILD_DLL
	#else
		#define TOY_API
	#endif
#else
	#error Toy only support Windows!
#endif // TOY_PLATFORM_WINDOWS

#ifdef TOY_DEBUG
#define TOY_ENABLE_ASSERTS
#endif

#ifdef TOY_ENABLE_ASSERTS
#define TOY_ASSERT(x, ...) { if(!(x)) { TOY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define TOY_CORE_ASSERT(x, ...) { if(!(x)) { TOY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define TOY_ASSERT(...)
#define TOY_CORE_ASSERT(...)
#endif // TOY_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define TOY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)