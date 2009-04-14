#pragma once
//#include "vss_stdinc.h"
#include "Settings.h"

class Exhaust;

class ExhaustSettings : public Settings {
	
	public:
		ExhaustSettings(Exhaust *p);
		void callbackSet(int p);
		Exhaust *parent;

};