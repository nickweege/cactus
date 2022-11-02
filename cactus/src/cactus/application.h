#pragma once

#include "events/event.h"
#include "window.h"

namespace cactus {

	class application {
	public:
		application();
		virtual ~application();
		void run();
	private:
		std::unique_ptr<window> m_window;
		bool m_running = true;
	};

	application* create_application();
}