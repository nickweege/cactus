#include "cactuspch.h"
#include "windows_window.h"
#include "cactus/events/application_event.h"
#include "cactus/events/key_event.h"
#include "cactus/events/mouse_event.h"
#include "glad/glad.h"

namespace cactus {

	static bool s_is_GLFW_initialized;
	static void glfw_error_callback(int error, const char* desc) { CACTUS_CORE_ERROR("GLFW error ({0}): {1}", error, desc); }

	window* window::create(const window_props& props) { return new windows_window(props); }

	windows_window::windows_window(const window_props& props) { init(props); }

	windows_window::~windows_window() { shutdown(); }

	void windows_window::init(const window_props& props) {
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		if (!s_is_GLFW_initialized) {
			int success_flag = glfwInit();
			CACTUS_CORE_ASSERT(success_flag, "could not initialize glfw");
			glfwSetErrorCallback(glfw_error_callback);
			s_is_GLFW_initialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		int ststus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CACTUS_CORE_ASSERT(status, "could not initialize glad");

		glfwSetWindowUserPointer(m_window, &m_data);
		set_vsync(true);

		// GLFW CALLBACKS
		// 
		// application/window callbacks
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			window_close_event event;
			data.event_callback(event);
		});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			window_resize_event event(width, height);
			data.event_callback(event);
		});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			if (focused == GLFW_TRUE) {
				window_focus_event event;
				data.event_callback(event);
			}
			if (focused == GLFW_FALSE) {
				window_lost_focus_event event;
				data.event_callback(event);
			}
		});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			window_moved_event event(xpos, ypos);
			data.event_callback(event);
		});

		// mouse callbacks
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					mouse_button_pressed_event event(button);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE: {
					mouse_button_released_event event(button);
					data.event_callback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			mouse_moved_event event((float)xpos, (float)ypos);
			data.event_callback(event);
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			mouse_scrolled_event event((float)xoffset, (float)yoffset);
			data.event_callback(event);
		});

		// keyboard callbacks
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					key_pressed_event event(key, 0);
					data.event_callback(event);
					break;
				}
				case GLFW_REPEAT: {
					key_pressed_event event(key, 1);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE: {
					key_released_event event(key);
					data.event_callback(event);
					break;
				}
			}
		});

		CACTUS_CORE_INFO("GLFW window (\"{0}\" {1} x {2}) created", props.title, props.width, props.height);
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