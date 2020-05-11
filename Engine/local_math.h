#pragma once

int clamp(int min, int val, int max);

float lerp(float v0, float v1, float t);

#define SIGN(x) (x > 0) - (x < 0)