#pragma once

#include "events/event.h"

namespace cactus {

	class layer {
	public:
		layer(const std::string& name = "layer");
		virtual ~layer();
		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update() {}
		virtual void on_event(event& event) {}
		inline const std::string& get_name() const { return m_debug_name; }
	protected:
		std::string m_debug_name;
	};
}