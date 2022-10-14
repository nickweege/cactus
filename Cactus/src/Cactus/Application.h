#pragma once

#include "Core.h"

namespace Cactus {
	class Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();
}