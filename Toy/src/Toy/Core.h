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
