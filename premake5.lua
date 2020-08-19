workspace "onewknd"
	architecture "x86_64"
    startproject "onewknd"
    filename "onewknd"
    location "./"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution directory)
	--[[
	IncludeDir = {}
	IncludeDir["GLFW"] = "../efgl/vendor/GLFW/include"
	IncludeDir["Glad"] = "../efgl/vendor/Glad/include"
	IncludeDir["stb"]  = "../efgl/vendor/stb"
	IncludeDir["glm"]  = "../efgl/vendor/glm"
	IncludeDir["spdlog"] = "../efgl/vendor/spdlog/include"
	--]]
	--[[
	group "Dependencies"
		include "../efgl/vendor/GLFW"
		include "../efgl/vendor/Glad"
	--]]
	project "onewknd"
		location "../onewknd/%{prj.name}"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
		objdir ("/bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"../%{prj.name}/src/**"
		}

		includedirs
		{
			"/%{prj.name}/src",
			"/vendor",
			--[[
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb}",
			"%{IncludeDir.spdlog}"
			--]]
		}
		--[[
		links
		{
			"efgl"
		}
		--]]
			
		filter "configurations:Debug"
			defines "EF_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "EF_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "EF_DIST"
			runtime "Release"
			optimize "on"