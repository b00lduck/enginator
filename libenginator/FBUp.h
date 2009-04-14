#pragma once
#include "vss_stdinc.h"
#include "ChainElement.h"
#include "LPFilt.h"

class FBUp : public ChainElement {
	public:
		FBUp(float k, float co, float ord);
		~FBUp();
		void setup();
		void transform();
		LPFilt *fb_filt;
};