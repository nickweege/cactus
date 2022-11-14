#pragma once

#include "event.h"

namespace cactus {

	class mouse_button_event : public event {
	public:
		inline int get_mouse_button() const { return m_mouse_button; }
		EVENT_CLASS_CATEGORY(mouse_category | input_category)
	protected:
		mouse_button_event(int mouse_button) : m_mouse_button(mouse_button) {}
		int m_mouse_button;
	};

	class mouse_button_pressed_event : public mouse_button_event {
	public:
		mouse_button_pressed_event(int mouse_button) : mouse_button_event(mouse_button) {}
		EVENT_CLASS_TYPE(mouse_button_pressed)

			std::string to_string() const override {
			std::stringstream log;
			log << "mouse_button_pressed_event: " << m_mouse_button;
			return log.str();
		}
	};

	class mouse_button_released_event : public mouse_button_event {
	public:
		mouse_button_released_event(int mouse_button) : mouse_button_event(mouse_button) {}
		EVENT_CLASS_TYPE(mouse_button_released)

			std::string to_string() const override {
			std::stringstream log;
			log << "mouse_button_released_event: " << m_mouse_button;
			return log.str();
		}
	};

	class mouse_moved_event : public event {
	public:
		mouse_moved_event(float xpos, float ypos) : m_xpos(xpos), m_ypos(ypos) {}
		inline float get_mouse_x() const { return m_xpos; }
		inline float get_mouse_y() const { return m_ypos; }
		EVENT_CLASS_TYPE(mouse_moved)
		EVENT_CLASS_CATEGORY(mouse_category | input_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "mouse_moved_event: x:" << m_xpos << ", y:" << m_ypos;
			return log.str();
		}
	private:
		float m_xpos;
		float m_ypos;
	};

	class mouse_scrolled_event : public event {
	public:
		mouse_scrolled_event(float xoffset, float yoffset) : m_xoffset(xoffset), m_yoffset(yoffset) {}
		inline float get_x_offset() const { return m_xoffset; }
		inline float get_y_offset() const { return m_yoffset; }
		EVENT_CLASS_TYPE(mouse_scrolled)
		EVENT_CLASS_CATEGORY(mouse_category | input_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "mouse_scrolled_event: " << m_xoffset << ", " << m_yoffset;
			return log.str();
		}
	private:
		float m_xoffset;
		float m_yoffset;
	};
}