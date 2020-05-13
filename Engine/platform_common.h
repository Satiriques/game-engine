#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

struct {
	// platform non-specific
	int width, height;
	uint32_t* pixels;

	// plateform specific
	BITMAPINFO bitmap_info;
} typedef Render_Buffer;

struct {
	bool is_down;
	bool changed;
} typedef Button;

enum {
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,

	BUTTON_COUNT,
};

struct {
	int mouse_x;
	int mouse_y;

	Button buttons[BUTTON_COUNT];
} typedef Input;