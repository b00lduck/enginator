#pragma once
#include "vss_stdinc.h"
#include "FBUp.h"

FBUp::FBUp( float k, float co, float ord) : ChainElement() {
	fb_filt = new LPFilt(co,k,ord);
}

FBUp::~FBUp() {
	delete(fb_filt);
}

void FBUp::setup() {}

void FBUp::transform() {
	c = d;
	b = a + lastin + fb_filt->tick(d);
}