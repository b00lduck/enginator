#pragma once
#include "vss_stdinc.h"

class IIR {

	public:
		IIR();
		~IIR();

		void setLowpass(int o, float c, float g);
		float tick(float in);
		float tickHP(float in);

	private:
		float *buffer;
		float cutoff;
		float cutoff_a;
		float gain;
		int order;

};

