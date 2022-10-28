#pragma once

enum window_mode {
	FULLSCREEN,
	BORDERLESS,
	WINDOWED
};

class window {
public:
	static bool m_window_keys[256];
	static int m_mouse_x_pos;
	static int m_mouse_y_pos;

	window();

	HINSTANCE get_inst_handle() const;
	HWND get_window_handle() const;
	HICON get_window_icon() const;
	HCURSOR get_window_cursor() const;
	/*
	std::string get_window_title() const;
	DWORD get_window_style() const;
	COLORREF get_window_color() const;
	int get_window_mode() const;
	int get_window_width() const;
	int get_window_height() const;
	int get_window_x_pos() const;
	int get_window_y_pos() const;
	float get_window_x_center() const;
	float get_window_y_center() const;
	*/

	void set_icon(const unsigned int icon);
	void set_cursor(const unsigned int cursor);
	void set_title(const std::string title);
	void set_mode(int mode);
	void set_size(int width, int height);
	void set_color(int r, int g, int b);
	void hide_cursor(bool hide_flag);
	bool key_down(int key_code);
	bool key_up(int key_code);
	bool create_window();
	void close_window();
	static LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_inst_handle;
	HWND m_window_handle;
	HICON m_window_icon;
	HCURSOR m_window_cursor;
	std::string m_window_title;
	DWORD m_window_style;
	COLORREF m_window_color;
	int m_window_mode;
	int m_window_width;
	int m_window_height;
	int m_window_x_pos;
	int m_window_y_pos;
	float m_window_x_center;
	float m_window_y_center;
};
// getters
inline HINSTANCE window::get_inst_handle() const { return m_inst_handle; }

inline HWND window::get_window_handle() const { return m_window_handle; }

inline HICON window::get_window_icon() const { return m_window_icon; }

inline HCURSOR window::get_window_cursor() const { return m_window_cursor; }
// ...

// setters
inline void window::set_icon(const unsigned int icon) { m_window_icon = LoadIcon(m_inst_handle, MAKEINTRESOURCE(icon)); }

inline void window::set_cursor(const unsigned int cursor) { m_window_cursor = LoadCursor(m_inst_handle, MAKEINTRESOURCE(cursor)); }

inline void window::set_title(const std::string title) { m_window_title = title; }

inline void window::set_color(int r, int g, int b) { m_window_color = RGB(r, g, b); }

inline void window::hide_cursor(bool hideFlag) { ShowCursor(!hideFlag); }

inline bool window::key_down(int key_code) { return m_window_keys[key_code]; }

inline bool window::key_up(int key_code) { return m_window_keys[key_code]; }

inline void window::close_window() { PostMessage(m_window_handle, WM_DESTROY, 0, 0); }