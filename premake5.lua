-- premake5.lua

workspace "Cactus"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }

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

   filter "configurations:Debug"
      defines "CACTUS_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "CACTUS_RELEASE"
      optimize "On"

   filter "configurations:Dist"
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

   filter "configurations:Debug"
      defines "CACTUS_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "CACTUS_RELEASE"
      optimize "On"

   filter "configurations:Dist"
      defines "CACTUS_DIST"
      optimize "On"