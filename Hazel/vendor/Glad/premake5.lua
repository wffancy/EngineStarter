project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    sysincludedirs { "%{prj.name}/vendor/spdlog/include" }

    filter "system:macosx"
        staticruntime "On"
        cppdialect "C++17"