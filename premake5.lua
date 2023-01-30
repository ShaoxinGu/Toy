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
-- Include directories relatives to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Toy/vendor/GLFW/include"
IncludeDir["Glad"] = "Toy/vendor/Glad/include"
IncludeDir["ImGui"] = "Toy/vendor/imgui"

group "Dependencies"
	include "Toy/vendor/GLFW"
	include "Toy/vendor/Glad"
	include "Toy/vendor/imgui"

group ""


project "Toy"
	location "Toy"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "toypch.h"
	pchsource "Toy/src/toypch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"TOY_PLATFORM_WINDOWS",
			"TOY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "TOY_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "TOY_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "TOY_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		systemversion "latest"

		defines
		{
			"TOY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOY_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "TOY_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "TOY_DIST"
		runtime "Release"
		optimize "On"