#pragma once

#include "events/event.h"
#include "events/application_event.h"
#include "window.h"

namespace cactus {

	class application {
	public:
		application();
		virtual ~application();
		void on_event(event& event);
		void run();
	private:
		bool on_window_close(window_close_event& event);
		std::unique_ptr<window> m_window;
		bool m_running = true;
	};

	application* create_application();
}