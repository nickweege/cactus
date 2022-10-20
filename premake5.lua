-- premake5.lua

workspace "Cactus"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cactus"
   location "Cactus"
   kind "StaticLib"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
   includedirs { "%{prj.name}/vendor/spdlog/include" }

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

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
   includedirs { "Cactus/vendor/spdlog/include", "Cactus/src" }
   links { "Cactus" }

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