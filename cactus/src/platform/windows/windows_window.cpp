#include "cactuspch.h"
#include "windows_window.h"

namespace cactus {

	static bool s_is_GLFW_initialized;

	window* window::create(const window_props& props) { return new windows_window(props); }

	windows_window::windows_window(const window_props& props) { init(props); }

	windows_window::~windows_window() { shutdown(); }

	void windows_window::init(const window_props& props) {
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		// CACTUS_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.height, props.width);

		if (!s_is_GLFW_initialized) {
			int success_flag = glfwInit();
			CACTUS_CORE_ASSERT(success_flag, "Could not initialize glfw");
			s_is_GLFW_initialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		set_vsync(true);
	}

	void windows_window::shutdown() {
		glfwDestroyWindow(m_window);
	}

	void windows_window::on_update() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void windows_window::set_vsync(bool set_flag) {
		if (set_flag)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = set_flag;
	}

	bool windows_window::is_vsync() const { return m_data.vsync; }
}