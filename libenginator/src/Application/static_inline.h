#pragma once

static inline float MIN(float a, float b) {
	if (a > b) return b;
	return a;
}

static inline float MAX(float a, float b) {
	if (a < b) return b;
	return a;
}

