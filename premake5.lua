workspace "EngineStarter"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
    location "Hazel"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "src/hzpch.h"

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/GLFW/include"
    }

    libdirs { "%{prj.name}/vendor/GLFW/lib" }

    links 
    { 
        "glfw3",
        "OpenGL.framework",
        "Cocoa.framework",
        "IOKit.framework",
    }

    sysincludedirs { "%{prj.name}/vendor/spdlog/include" }

    filter "system:macosx"
        staticruntime "On"
        cppdialect "C++17"

        defines
        {
            "HZ_PLATFORM_MAC",
            "HZ_BUILD_DLL",
            "HZ_ENABLE_ASSERTS"
        }

        postbuildcommands
        {

        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        
    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hazel",
        "Hazel/src",
        "Hazel/vendor/spdlog/include",
    }

    sysincludedirs { "Hazel/vendor/spdlog/include" }

    links
    {
        "Hazel",
    }

    filter "system:macosx"
        staticruntime "On"
        cppdialect "C++17"

        defines
        {
            "HZ_PLATFORM_MAC"
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        
    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"

    