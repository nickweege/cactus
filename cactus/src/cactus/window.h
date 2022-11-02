#pragma once

#include "cactuspch.h"
#include "events/event.h"

namespace cactus {

	struct window_props {
		std::string title;
		unsigned int width;
		unsigned int height;

		window_props(const std::string& title = "Cactus",
			unsigned int width = 1280,
			unsigned int height = 720)
			: title(title), width(width), height(height) {}
	};

	class window {
	public:
		using event_callback_fn = std::function<void(event&)>;
		virtual ~window() {}
		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;
		virtual void set_vsync(bool set_flag) = 0;
		virtual bool is_vsync() const = 0;
		virtual void on_update() = 0;
		virtual void set_event_callbak(const event_callback_fn& callback) = 0;
		static window* create(const window_props& props = window_props());
	};
}