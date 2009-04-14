#pragma once
#include "vss_stdinc.h"
#include "ChainElement.h"
#include "LPFilt.h"

class FBDown : public ChainElement {
	public:	
		FBDown(float k, float co, float ord);
		~FBDown();
		void setup();
		void transform();
		LPFilt *fb_filt;
};