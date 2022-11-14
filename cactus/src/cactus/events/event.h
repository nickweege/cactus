#pragma once

#include "cactuspch.h"
#include "cactus/core.h"

namespace cactus {

	enum class event_type {
		none = 0,
		window_close, window_resize, window_focus, window_lost_focus, window_moved,
		mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled,
		key_pressed, key_released
	};

	enum event_category {
		none = 0,
		application_category = BIT(0),
		input_category       = BIT(1),
		keyboard_category    = BIT(2),
		mouse_category       = BIT(3),
		mouse_btn_category   = BIT(4)
	};

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

#define EVENT_CLASS_TYPE(type) static event_type get_static_type() { return event_type::##type; }\
	                           virtual event_type get_event_type() const override { return get_static_type(); }\
	                           virtual const char* get_name() const override { return #type; }

	class event {
		friend class event_dispatcher;
	public:
		virtual event_type get_event_type() const = 0;
		virtual int get_category_flags() const = 0;
		virtual const char* get_name() const = 0;
		virtual std::string to_string() const { return get_name(); }
		inline bool is_in_category(event_category category) { return get_category_flags() & category; }
	protected:
		bool m_handled = false;
	};

	class event_dispatcher {
		template<typename T> using event_fn = std::function<bool(T&)>;
	public:
		event_dispatcher(event& event) : m_event(event) {}

		template<typename T>
		bool dispatch(event_fn<T> func) {
			if (m_event.get_event_type() == T::get_static_type()) {
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const event& e) { return os << e.to_string(); }
}