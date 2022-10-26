#pragma once

#include "event.h"
#include <sstream>

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
		mouse_moved_event(float x_pos, float y_pos) : m_x_pos(x_pos), m_y_pos(y_pos) {}
		inline float get_mouse_x() const { return m_x_pos; }
		inline float get_mouse_y() const { return m_y_pos; }
		EVENT_CLASS_TYPE(mouse_moved)
		EVENT_CLASS_CATEGORY(mouse_category | input_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "mouse_moved_event: " << m_x_pos << ", " << m_y_pos;
			return log.str();
		}
	private:
		float m_x_pos;
		float m_y_pos;
	};

	class mouse_scrolled_event : public event {
	public:
		mouse_scrolled_event(float x_offset, float y_offset) : m_x_offset(x_offset), m_y_offset(y_offset) {}
		inline float get_x_offset() const { return m_x_offset; }
		inline float get_y_offset() const { return m_y_offset; }
		EVENT_CLASS_TYPE(mouse_scrolled)
		EVENT_CLASS_CATEGORY(mouse_category | input_category)

		std::string to_string() const override {
			std::stringstream log;
			log << "mouse_scrolled_event: " << m_x_offset << ", " << m_y_offset;
			return log.str();
		}
	private:
		float m_x_offset;
		float m_y_offset;
	};
}