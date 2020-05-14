#pragma once

#include <stdint.h>
#include "engine.h"
#include "local_math.h"
#include <math.h>
#include "platform_common.h"

void clear_screen(Render_Buffer buffer, uint32_t color);

void draw_rect_in_pixels(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2);

void draw_rect(Render_Buffer buffer, v2 p, v2 half_size, uint32_t color);

void draw_pixel(Render_Buffer buffer, uint32_t color, int x, int y);

void draw_line_in_pixels(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2);

void draw_bitmap(Render_Buffer buffer, char* file, int x1, int y1, uint32_t transparency);
