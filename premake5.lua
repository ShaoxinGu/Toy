workspace "Toy"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "Sandbox"

project "Toy"
	location "Toy"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src;",
		"%{prj.name}/vendor/spdlog/include;"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TOY_BUILD_DLL",
			"TOY_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "TOY_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "TOY_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "TOY_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Toy/vendor/spdlog/include",
		"Toy/src"
	}

	links
	{
		"Toy"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TOY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOY_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "TOY_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "TOY_DIST"
		optimize "On"
