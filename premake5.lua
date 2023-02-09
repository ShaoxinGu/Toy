workspace "Toy"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relatives to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Toy/vendor/GLFW/include"
IncludeDir["Glad"] = "Toy/vendor/Glad/include"
IncludeDir["ImGui"] = "Toy/vendor/imgui"
IncludeDir["glm"] = "Toy/vendor/glm"

group "Dependencies"
	include "Toy/vendor/GLFW"
	include "Toy/vendor/Glad"
	include "Toy/vendor/imgui"
group ""

project "Toy"
	location "Toy"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "toypch.h"
	pchsource "Toy/src/toypch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOY_PLATFORM_WINDOWS",
			"TOY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TOY_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "TOY_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "TOY_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Toy/src",
		"Toy/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Toy"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOY_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "TOY_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "TOY_DIST"
		runtime "Release"
		optimize "on"