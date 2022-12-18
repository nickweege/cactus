#pragma once

#include "events/event.h"
#include "events/application_event.h"
#include "events/mouse_event.h"
#include "window.h"
#include "layer_stack.h"

namespace cactus {

	class application {
	public:
		application();
		virtual ~application();
		void on_event(event& event);
		void run();
		void push_layer(layer* layer);
		void push_overlay(layer* overlay);
		inline window& get_window() const { return *m_window; }
		inline static application& get() { return *s_instance; }
	private:
		static application* s_instance;

		bool on_window_close(window_close_event& event);
		bool on_window_resize(window_resize_event& event);

		std::unique_ptr<window> m_window;
		layer_stack m_layer_stack;
		bool m_running = true;
	};

	application* create_application();
}