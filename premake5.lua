workspace "OpenGL"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist",
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


Dir = {}
Dir["GLFW"] = "OpenGL/vendor/GLFW"

project "OpenGL"
    location "OpenGL"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")


    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{Dir.GLFW}/include"
    }

    libdirs
    {
        "%{Dir.GLFW}/lib"
    }

    links
    {
        "glfw3",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        buildoptions {"/utf-8"}

        defines
        {
        }

    filter "configurations:Debug"
        buildoptions "/MDd"
        runtime "Debug"
        defines "BH_DEBUG"
        symbols "On"


    filter "configurations:Release"
        buildoptions "/MD"
        runtime "Release"   
        defines "BH_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        buildoptions "/MD"
        runtime "Release"
        defines "BH_DIST"
        optimize "On"
