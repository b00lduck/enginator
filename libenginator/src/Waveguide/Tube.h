#pragma once
#include "vss_stdinc.h"
#include "ChainElement.h"
#include "floatDelayLine.h"
#include "LPFilt.h"
#include "Noise.h"

class Tube : public ChainElement {
	public:
		Tube(DWORD len, float R, float k, float co, float ord);
		~Tube();
		void setup();
		void transform();
		floatDelayLine *delay;
		LPFilt *filt1;
		LPFilt *filt2;
		int len;
		float noisefac;

		Noise *noise1,*noise2;

		void setLen(float len);
		void setR(float r);
};