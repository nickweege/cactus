#pragma once

#include "event.h"

namespace cactus {

	class window_close_event : public event {
	public:
		window_close_event() {}
		EVENT_CLASS_TYPE(window_close)
		EVENT_CLASS_CATEGORY(application_category)
	};

	class window_resize_event : public event {
	public:
		window_resize_event(unsigned int width, unsigned int height) : m_window_width(width), m_window_height(height) {}
		inline int get_window_width() const { return m_window_width; }
		inline int get_window_height() const { return m_window_height; }
		EVENT_CLASS_TYPE(window_resize)
		EVENT_CLASS_CATEGORY(application_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "window_resize_event: " << m_window_width << ", " << m_window_height;
			return log.str();
		}
	private:
		unsigned int m_window_width;
		unsigned int m_window_height;
	};
}