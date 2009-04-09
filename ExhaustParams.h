#pragma once
//#include "vss_stdinc.h"
#include "Params.h"

class Exhaust;

class ExhaustParams : public Params {
	
	public:
		ExhaustParams(Exhaust *p);
		void callbackSet(int p);
		Exhaust *parent;

};