#pragma once
#include "vss_stdinc.h"
#include "Filt.h"

class HPFilt : public Filt {
	public:
		HPFilt(float cut, float g, int ord);
		float tick(float in);

};