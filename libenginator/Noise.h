#pragma once
#include "vss_stdinc.h"

class Noise {

	public:
		Noise();
		float tick();
	private:
		float b0,b1,b2,b3,b4,b5,b6;
};

