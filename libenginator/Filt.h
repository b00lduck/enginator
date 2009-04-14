#pragma once
#include "vss_stdinc.h"

#define MAXFORD 128

class Filt {
	public:
		Filt(float cut, float g, int ord);
		~Filt();
		void setCutoff(float cut);
		void setGain(float g);
		float cutoff,cutoff_a;
		float gain;
		int order;
		float *buffer;
};






