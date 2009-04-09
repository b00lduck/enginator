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
	Limiter *myLimiter;

  private:
	float left,right;

	float getTiming(float start, float end, float ph);

	IIR *myHPL;
	IIR *myHPR;

};

extern Synth* g_pSynth;