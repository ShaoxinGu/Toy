#pragma once

#ifdef TOY_PLATFORM_WINDOWS
	#if TOY_BUILD_DLL
		#define TOY_API __declspec(dllexport)
	#else
		#define TOY_API __declspec(dllimport)
	#endif // TOY_BUILD_DLL
#else
	#error Toy only support Windows!
#endif // TOY_PLATFORM_WINDOWS

#ifdef TOY_ENABLE_ASSERTS
#define TOY_ASSERT(...) { if(!(x)) { TOY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define TOY_CORE_ASSERT(...) { if(!(x)) { TOY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define TOY_ASSERT(...)
#define TOY_CORE_ASSERT(...)
#endif // TOY_ENABLE_ASSERTS

#define BIT(x) (1 << x)
