/* Learning to make a game engine using this
   https://github.com/DanZaidan/break_arcade_games_out
*/

#include "engine.h"


static bool running = true;
Render_Buffer render_buffer;

LRESULT CALLBACK window_callback(_In_ HWND window,
	_In_ UINT   message,
	_In_ WPARAM w_param,
	_In_ LPARAM l_param
) {
	LRESULT result = 0;

	switch (message) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;

		//GetWindowRect also includes the toolbar, this doesn't
		GetClientRect(window, &rect);
		render_buffer.width = rect.right - rect.left;
		render_buffer.height = rect.bottom - rect.top;

		if (render_buffer.pixels) {
			VirtualFree(render_buffer.pixels, 0, MEM_RELEASE);
		}

		render_buffer.pixels = VirtualAlloc(0, sizeof(uint32_t) * render_buffer.width * render_buffer.height,
			MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_buffer.bitmap_info.bmiHeader.biSize = sizeof(render_buffer.bitmap_info.bmiHeader);
		render_buffer.bitmap_info.bmiHeader.biWidth = render_buffer.width;
		render_buffer.bitmap_info.bmiHeader.biHeight = render_buffer.height;
		render_buffer.bitmap_info.bmiHeader.biPlanes = 1;
		render_buffer.bitmap_info.bmiHeader.biBitCount = 32;
		render_buffer.bitmap_info.bmiHeader.biCompression = BI_RGB;
		break;
	}

	default: {
		result = DefWindowProcA(window, message, w_param, l_param);
	}
	}

	return result;
}

int __stdcall WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {
	WNDCLASSA window_class = { 0 };

	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = window_callback;
	window_class.lpszClassName = "Game_Window_Class";

	Input input = { 0 };

	RegisterClassA(&window_class);

	HWND window = CreateWindowExA(0, window_class.lpszClassName, "Breakout",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 1280, 720, 0, 0, 0, 0);

	HDC hdc = GetDC(window);
	int character = false;

	while (running) {
		// Input
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		MSG message;
		while (PeekMessageA(&message, window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
			case WM_KEYDOWN:
			case WM_KEYUP: {
				uint32_t vk_code = (uint32_t)message.wParam;
				bool was_down = ((message.lParam & (1 << 30)) != 0);
				bool is_down = ((message.lParam & (1 << 31)) == 0);


#define process_button(vk, b) \
	if (vk_code == vk) { \
		input.buttons[b].changed = is_down != input.buttons[b].is_down; \
		input.buttons[b].is_down = is_down; \
	}
				process_button(VK_LEFT, BUTTON_LEFT);
				process_button(VK_RIGHT, BUTTON_RIGHT);
				process_button(VK_DOWN, BUTTON_DOWN);
				process_button(VK_UP, BUTTON_UP);

			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}


		// Simulation
		clear_screen(render_buffer, 0xffff00);

		// todo: dt
		update_game(&input, render_buffer, 0.01666f);
		/*

		if (character) {
			draw_rect(render_buffer, 0xFF0000, 10, 10, 100, 100);
			draw_line(render_buffer, 0xFF00FF, 0, 0, 100, 100);

		}*/
		//draw_bitmap(render_buffer, "..\\..\\..\\..\\Pictures\\max.jpg", 100, 100, 0x00FF00);

		// Render
		StretchDIBits(hdc, 0, 0, render_buffer.width, render_buffer.height, 0, 0, render_buffer.width,
			render_buffer.height, render_buffer.pixels, &render_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}