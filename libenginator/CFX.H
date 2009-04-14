#pragma once
#include "vss_stdinc.h"

class CFX {

	public:
		CFX();
		void tick_mono(float *pDataIn, float *pDataOut, DWORD length);
		void tick_stereo(float* pDataIn, float* pDataL, float* pDataR, DWORD length);		
	
		virtual void tick(float input) { };
		float lastOutput[2];
		float effectMix;

	protected:
		bool isPrime(int number);

};