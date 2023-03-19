workspace "VM"
    configurations {"Debug", "Release"}
    location "build"

project "VM"
    kind "ConsoleApp"
    language "C++"
    architecture "x64"
    cppdialect "c++latest"
    targetdir "bin/%{cfg.buildcfg}"

files {"src/**.cpp"}
includedirs {"include"}

filter "configurations:Debug"
    defines {"DEBUG"}
    symbols "On"
    
filter "configurations:Release"
    defines {"NDEBUG"}
    optimize "On"

