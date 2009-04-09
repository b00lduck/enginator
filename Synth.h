#pragma once
#include "vss_stdinc.h"
#include "Engine.h"
#include "Exhaust.h"
#include "Intake.h"
#include "Limiter.h"

class Synth {
  
	public:
		Synth();
		~Synth();
		void synthRender(float* pDataL, float* pDataR, DWORD length_samples);

		Engine *myEngine;
		Exhaust *myExhaust1;
		Exhaust *myExhaust2;
		Intake *myIntake;

		void setThrottle(float throttle);
		void setRPM(float rpm);
		void setIgnition(bool ignition);

	private:

		float left,right;
		IIR *myHPL;
		IIR *myHPR;
		Limiter *myLimiter;

};

extern Synth* g_pSynth;