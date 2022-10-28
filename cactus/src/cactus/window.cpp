#include "cactuspch.h"
#include "window.h"

bool window::m_window_keys[256] = { 0 };
int window::m_mouse_x_pos;
int window::m_mouse_y_pos;

window::window() {
	m_inst_handle = GetModuleHandle(NULL);
	m_window_handle = 0;
	m_window_icon = LoadIcon(m_inst_handle, IDI_APPLICATION);
	m_window_cursor = LoadCursor(m_inst_handle, IDC_ARROW);
	m_window_title = std::string("cactus");
	m_window_style = WS_POPUP | WS_VISIBLE;
	m_window_color = RGB(0, 0, 0);
	m_window_mode = FULLSCREEN;
	m_window_width = GetSystemMetrics(SM_CXSCREEN);
	m_window_height = GetSystemMetrics(SM_CYSCREEN);
	m_window_x_pos = 0;
	m_window_y_pos = 0;
	m_window_x_center = m_window_width / 2.0f;
	m_window_y_center = m_window_height / 2.0f;
}

void window::set_mode(int mode) {
	m_window_mode = mode;

	switch (mode) {
	case BORDERLESS:
		m_window_style = WS_POPUP | WS_VISIBLE;
		return;

	case FULLSCREEN:
		m_window_style = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE;
		return;

	case WINDOWED:
		m_window_style = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;
		return;
	}
}

void window::set_size(int width, int height) {
	m_window_width = width;
	m_window_height = height;

	m_window_x_center = m_window_width / 2.0f;
	m_window_y_center = m_window_height / 2.0f;

	m_window_x_pos = GetSystemMetrics(SM_CXSCREEN) / 2 - m_window_width / 2;
	m_window_y_pos = GetSystemMetrics(SM_CYSCREEN) / 2 - m_window_height / 2;
}

bool window::create_window() {
	WNDCLASSEX window_class;
	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = window::win_proc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = m_inst_handle;
	window_class.hIcon = m_window_icon;
	window_class.hIconSm = m_window_icon;
	window_class.hCursor = m_window_cursor;
	window_class.hbrBackground = (HBRUSH)GetStockObject(m_window_color);
	window_class.lpszMenuName = NULL;
	window_class.lpszClassName = L"game_window";

	if (!RegisterClassEx(&window_class))
		return false;

	m_window_handle = CreateWindowEx(NULL, L"GameWindow", L"Blockits", m_window_style,
		CW_USEDEFAULT, CW_USEDEFAULT, m_window_width, m_window_height, NULL, NULL, m_inst_handle, NULL);

	if (m_window_mode == WINDOWED) {
		RECT rect = { 0, 0, m_window_width, m_window_height };

		AdjustWindowRectEx(&rect, GetWindowStyle(m_window_handle),
			GetMenu(m_window_handle) != NULL, GetWindowExStyle(m_window_handle));

		m_window_x_pos = GetSystemMetrics(SM_CXSCREEN) / 2 - (rect.right - rect.left) / 2;
		m_window_y_pos = GetSystemMetrics(SM_CYSCREEN) / 2 - (rect.bottom - rect.top) / 2;

		MoveWindow(m_window_handle, m_window_x_pos, m_window_y_pos,
			rect.right - rect.left, rect.bottom - rect.top, TRUE);
	}

	return m_window_handle ? true : false;
}

LRESULT CALLBACK window::win_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KILLFOCUS:
		return 0;

	case WM_SETFOCUS:
		return 0;

	case WM_MOUSEMOVE:
		m_mouse_x_pos = GET_X_LPARAM(lParam);
		m_mouse_y_pos = GET_Y_LPARAM(lParam);
		return 0;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_KEYDOWN:
		m_window_keys[wParam] = true;
		return 0;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_KEYUP:
		m_window_keys[wParam] = false;
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}