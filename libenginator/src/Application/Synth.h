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
		void synthRenderBytes(unsigned char* pByteDataL, unsigned char* pByteDataR, DWORD length_samples);
		void synthRenderBytesCombined(unsigned char* pByteData, DWORD length_samples);

		void setThrottle(float throttle);
		void setRPM(float rpm);
		void setIgnition(bool ignition);		

		void click(int x, int y);
		void unclick();
		void move(int x, int y);
		void draw(HDC hdc);
		float getProbe(int probeId);

	private:

		float* pDataL;
		float* pDataR;

		Engine *myEngine;
		Exhaust *myExhaust;
		Intake *myIntake;

		Limiter *myLimiter;

		IIR *myHPL;
		IIR *myHPR;



};
