#pragma once

#include "cactus/window.h"
#include "GLFW/glfw3.h"

namespace cactus {

	class windows_window : public window {
	public:
		windows_window(const window_props& props);
		virtual ~windows_window();
		inline unsigned int get_width() const override { return m_data.width; }
		inline unsigned int get_height() const override { return m_data.height; }
		void set_vsync(bool set_flag) override;
		bool is_vsync() const override;
		void on_update() override;
		inline void set_event_callbak(const event_callback_fn& callback) override { m_data.event_callback = callback; }
	protected:
		virtual void init(const window_props& props);
		virtual void shutdown();
	private:
		GLFWwindow* m_window;

		struct window_data {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vsync;
			event_callback_fn event_callback;
		};
		window_data m_data;
	};
}