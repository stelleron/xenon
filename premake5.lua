-- premake5.lua
workspace "Xenon"
   architecture "x64"
   configurations {"Debug", "Release"}

project "xenon"
   kind "SharedLib"
   language "C++"
   cppdialect "C++11"
   targetdir "build"
   objdir "build/obj/"
   files {"xenon/**.cpp"}
   includedirs {"external/include/", "external/include/glad/", "xenon/"}
   libdirs {"external/lib/", "external/lib/glad/"}
   links {"SDL2", "glad", "soloud"}

   filter "configurations:Debug"
       defines {"DEBUG", "ENABLE_XENON_LOGGER"}
       symbols "On"

   filter "configurations:Release"
       defines { "NDEBUG" }
       optimize "On"

project "test"   
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++11"
   targetdir "build"
   objdir "build/obj/"
   files {"src/**.cpp"}
   includedirs {"external/include/", "external/include/glad/", "xenon/", "src/"}
   libdirs {"build/"}
   links {"xenon"}

   filter "configurations:Debug"
       defines {"DEBUG"}
       symbols "On"

   filter "configurations:Release"
       defines { "NDEBUG" }
       optimize "On"
