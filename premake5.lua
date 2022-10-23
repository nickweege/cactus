-- premake5.lua

workspace "cactus"
   architecture "x64"
   configurations { "debug", "release", "dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "cactus"
   location "cactus"
   kind "StaticLib"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
   includedirs { "%{prj.name}/third-party-libs/spdlog/include" }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines { "CACTUS_WINDOWS_PLATFORM" }

   filter "configurations:debug"
      defines "CACTUS_DEBUG"
      symbols "On"

   filter "configurations:release"
      defines "CACTUS_RELEASE"
      optimize "On"

   filter "configurations:dist"
      defines "CACTUS_DIST"
      optimize "On"

project "blockits"
   location "blockits"
   kind "ConsoleApp"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
   includedirs { "cactus/third-party-libs/spdlog/include", "cactus/src" }
   links { "cactus" }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines { "CACTUS_WINDOWS_PLATFORM" }

   filter "configurations:debug"
      defines "CACTUS_DEBUG"
      symbols "On"

   filter "configurations:release"
      defines "CACTUS_RELEASE"
      optimize "On"

   filter "configurations:dist"
      defines "CACTUS_DIST"
      optimize "On"