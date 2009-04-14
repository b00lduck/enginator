#pragma once
//#include "vss_stdinc.h"
#include "Settings.h"

class Intake;

class IntakeSettings : public Settings {
	
	public:
		IntakeSettings(Intake *p);
		void callbackSet(int p);
		Intake *parent;

};