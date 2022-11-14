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
			log << "window_resize_event: " << m_window_width << " x " << m_window_height;
			return log.str();
		}
	private:
		unsigned int m_window_width;
		unsigned int m_window_height;
	};

	class window_focus_event : public event {
	public:
		window_focus_event() {}
		EVENT_CLASS_TYPE(window_focus)
		EVENT_CLASS_CATEGORY(application_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "window_focus_event";
			return log.str();
		}
	};

	class window_lost_focus_event : public event {
	public:
		window_lost_focus_event() {}
		EVENT_CLASS_TYPE(window_lost_focus)
		EVENT_CLASS_CATEGORY(application_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "window_lost_focus_event";
			return log.str();
		}
	};

	class window_moved_event : public event {
	public:
		window_moved_event(int xpos, int ypos) : m_xpos(xpos), m_ypos(ypos) {}
		inline int get_window_xpos() const { return m_xpos; }
		inline int get_window_ypos() const { return m_ypos; }
		EVENT_CLASS_TYPE(window_moved)
		EVENT_CLASS_CATEGORY(application_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "window_moved_event: x:" << m_xpos << ", y:" << m_ypos;
			return log.str();
		}
	private:
		int m_xpos;
		int m_ypos;
	};
}