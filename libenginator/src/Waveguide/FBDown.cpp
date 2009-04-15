#pragma once
#include "vss_stdinc.h"
#include "FBDown.h"

FBDown::FBDown(float k, float co, float ord) : ChainElement() {
	fb_filt = new LPFilt(co,k,ord);
}

FBDown::~FBDown() {
	delete(fb_filt);
}

void FBDown::setup() {}

void FBDown::transform() {
	b = a;
	c = fb_filt->tick(b);
}