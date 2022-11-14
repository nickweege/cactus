#include "cactuspch.h"
#include "application.h"
#include "platform/windows/windows_window.h"

namespace cactus {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	application::application() {
		log::init();
		m_window = std::unique_ptr<window>(window::create());
		m_window->set_event_callbak(BIND_EVENT_FN(application::on_event));
	}

	application::~application() {}

	void application::on_event(event& e) {
		event_dispatcher dispatcher(e);

		dispatcher.dispatch<window_close_event>(BIND_EVENT_FN(application::on_window_close));

		CACTUS_CORE_TRACE("{0}", e);
	}

	void application::run() {
		while (m_running) {
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->on_update();
		}
	}

	bool application::on_window_close(window_close_event& event) {
		m_running = false;
		return true;
	}
}