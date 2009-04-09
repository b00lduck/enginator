#include "CFilter.h"

CFilter::CFilter() {
	Reset();
}

void CFilter::Reset() {
	yn = yn1 = yn2 = 0;
	xn = xn1 = xn2 = 0;
	Set(0.5, 0, 1);
}

void CFilter::Set(float freq, float res, float vol) {
	this->R = res; 	
	this->g = R*R;
	this->vol = vol;
	this->omega = 2*R*cos(PI2 * freq / (float)SAMPLERATE);
}

float CFilter::tick(float in) {
	xn = in;
	yn = xn - R*xn2 + omega*yn1 - g*yn2;
	xn2 = xn1; xn1 = xn;
	yn2 = yn1; yn1 = yn;
	return yn * vol;
}


