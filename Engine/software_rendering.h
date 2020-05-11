#pragma once

#include <stdint.h>
#include "engine.h"
#include "local_math.h"
#include <math.h>

void clear_screen(Render_Buffer buffer, uint32_t color);

void draw_rect(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2);

void draw_pixel(Render_Buffer buffer, uint32_t color, int x, int y);

void draw_line(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2);