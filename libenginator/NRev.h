#pragma once
#include "vss_stdinc.h"
#include "CFX.h"
#include "stk.h"

class NRev : public CFX {
	public:
		NRev(float T60, float mix);
		~NRev();
		void clear();
		void tick(float input);

	protected:  
		Delay *allpassDelays[8];
		Delay *combDelays[6];
		float allpassCoefficient;
		float combCoefficient[6];
		float lowpassState;
};