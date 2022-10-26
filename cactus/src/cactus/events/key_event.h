#pragma once

#include "event.h"
#include <sstream>

namespace cactus {

	class key_event : public event {
	public:
		inline int get_key_code() const { return m_key_code; }
		EVENT_CLASS_CATEGORY(keyboard_category | input_category)
	protected:
		key_event(int key_code) : m_key_code(key_code) {}
		int m_key_code;
	};

	class key_pressed_event : public key_event {
	public:
		key_pressed_event(int key_code, int repeat_count) : key_event(key_code), m_repeat_count(repeat_count) {}
		inline int get_repeat_count() const { return m_repeat_count; }
		EVENT_CLASS_TYPE(key_pressed)

		std::string to_string() const override {
			std::stringstream log;
			log << "key_pressed_event: " << m_key_code << " (" << m_repeat_count << " repeats)";
			return log.str();
		}
	private:
		int m_repeat_count;
	};

	class key_released_event : public key_event {
	public:
		key_released_event(int key_code) : key_event(key_code) {}
		EVENT_CLASS_TYPE(key_pressed)

		std::string to_string() const override {
			std::stringstream log;
			log << "key_released_event: " << m_key_code;
			return log.str();
		}
	};
}