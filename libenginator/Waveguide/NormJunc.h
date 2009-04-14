#pragma once
#include "vss_stdinc.h"
#include "ChainElement.h"

class NormJunc : public ChainElement {
	public:
		NormJunc(float k1);
		~NormJunc();
		void setup();
		void transform();
		float k1;
};