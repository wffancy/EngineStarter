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

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src"
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:macosx"
        staticruntime "On"
        cppdialect "C++17"

        defines
        {
            "HZ_PLATFORM_MAC",
            "HZ_BUILD_DLL"
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
        "Hazel/vendor/spdlog/include",
        "Hazel/src"
    }

    links
    {
        "Hazel"
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

    