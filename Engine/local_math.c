#include "math.h"
#include "local_math.h"
int clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

float lerp(float v0, float v1, float t) {
	return (1 - t) * v0 + t * v1;
}