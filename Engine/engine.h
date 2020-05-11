#pragma once

#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>

struct {
	// platform non-specific
	int width, height;
	uint32_t* pixels;

	// plateform specific
	BITMAPINFO bitmap_info;
} typedef Render_Buffer;