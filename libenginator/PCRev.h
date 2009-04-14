#pragma once
#include "vss_stdinc.h"
#include "CFX.h"
#include "stk.h"

class PRCRev : public CFX {
	public:
		PRCRev(float T60, float mix);
		~PRCRev();
		void clear();
		void setT60(float T60 );
		void tick(float input);

	protected:  
		Delay allpassDelays[2];
		Delay combDelays[2];
		float allpassCoefficient;
		float combCoefficient[2];

};