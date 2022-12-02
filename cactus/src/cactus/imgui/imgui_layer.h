#pragma once

#include "cactus/layer.h"

namespace cactus {

	class imgui_layer : public layer {
	public:
		imgui_layer();
		~imgui_layer();
		void on_attach() override;
		void on_detach() override;
		void on_update() override;
		void on_event(event& event) override;
	private:
		float m_time = 0.0f;
	};
}