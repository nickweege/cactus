#include "cactuspch.h"
#include "application.h"
#include "platform/windows/windows_window.h"
#include "glad/glad.h"

namespace cactus {

// #define CACTUS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	application* application::s_instance = nullptr;

	application::application() {
		CACTUS_CORE_ASSERT(!s_instance, "Application already exists.");
		s_instance = this;

		log::init();
		m_window = std::unique_ptr<window>(window::create());
		m_window->set_event_callbak(CACTUS_BIND_EVENT_FN(application::on_event));
	}

	application::~application() {}

	void application::on_event(event& event) {
		event_dispatcher dispatcher(event);
		dispatcher.dispatch<window_close_event>(CACTUS_BIND_EVENT_FN(application::on_window_close));
		dispatcher.dispatch<window_resize_event>(CACTUS_BIND_EVENT_FN(application::on_window_resize));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin();) {
			(*--it)->on_event(event);
			if (event.m_handled) break;
		}

		// CACTUS_CORE_TRACE(event);
	}

	void application::run() {
		while (m_running) {
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (layer* layer : m_layer_stack) layer->on_update();

			m_window->on_update();
		}
	}

	void application::push_layer(layer* layer) {
		m_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void application::push_overlay(layer* overlay) {
		m_layer_stack.push_overlay(overlay);
		overlay->on_attach();
	}

	bool application::on_window_close(window_close_event& event) {
		m_running = false;
		return true;
	}

	bool application::on_window_resize(window_resize_event& event) { return true; }
}