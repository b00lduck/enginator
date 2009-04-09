#pragma once
#include "Filt.h"

class LPFilt : public Filt {
	public:
		LPFilt(float cut, float g, int ord);
		float tick(float in);
};