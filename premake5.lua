-- premake5.lua

workspace "cactus"
   architecture "x64"
   configurations { "debug", "release", "dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "cactus/third-party-libs/spdlog/include"
IncludeDir["glfw"] = "cactus/third-party-libs/glfw/include"
IncludeDir["glad"] = "cactus/third-party-libs/glad/include"
IncludeDir["imgui"] = "cactus/third-party-libs/imgui"

include "cactus/third-party-libs/glfw"
include "cactus/third-party-libs/glad"
include "cactus/third-party-libs/imgui"

-- CACTUS Engine Project's Configurations
project "cactus"
   location "cactus"
   kind "StaticLib"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
   includedirs { "%{prj.name}/src", "%{IncludeDir.spdlog}", "%{IncludeDir.glfw}", "%{IncludeDir.glad}", "%{IncludeDir.imgui}" }
   links { "glfw", "glad", "imgui", "opengl32.lib" }

   pchheader "cactuspch.h"
   pchsource "%{prj.name}/src/cactuspch.cpp"

   filter "system:windows"
      -- buildoptions "/MDd"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines { "CACTUS_WINDOWS_PLATFORM", "GLFW_INCLUDE_NONE" }

   filter "configurations:debug"
      defines "CACTUS_DEBUG"
      buildoptions "/MDd"
      symbols "On"

   filter "configurations:release"
      defines "CACTUS_RELEASE"
      buildoptions "/MD"
      optimize "On"

   filter "configurations:dist"
      defines "CACTUS_DIST"
      buildoptions "/MD"
      optimize "On"
 
-- BLOCKITS Project's Configurations
project "blockits"
   location "blockits"
   kind "ConsoleApp"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
   includedirs { "cactus/src", "%{IncludeDir.spdlog}" }
   links { "cactus" }

   filter "system:windows"
      -- buildoptions "/MDd"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines { "CACTUS_WINDOWS_PLATFORM" }

   filter "configurations:debug"
      defines "CACTUS_DEBUG"
      buildoptions "/MDd"
      symbols "On"

   filter "configurations:release"
      defines "CACTUS_RELEASE"
      buildoptions "/MD"
      optimize "On"

   filter "configurations:dist"
      defines "CACTUS_DIST"
      buildoptions "/MD"
      optimize "On"