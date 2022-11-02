#include "cactuspch.h"
#include "application.h"
#include "platform/windows/windows_window.h"

namespace cactus {

	application::application() {
		m_window = std::unique_ptr<window>(window::create());
	}

	application::~application() {}

	void application::run() {
		while (m_running) {
			m_window->on_update();
		}
	}
}