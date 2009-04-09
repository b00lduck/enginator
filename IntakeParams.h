#pragma once
//#include "vss_stdinc.h"
#include "Params.h"

class Intake;

class IntakeParams : public Params {
	
	public:
		IntakeParams(Intake *p);
		void callbackSet(int p);
		Intake *parent;

};