#pragma once
#include "vss_stdinc.h"
#include "ExhaustParams.h"
#include "perfWaveGuide.h"
#include "Resonator.h"
#include "Noise.h"
#include "LPFilt.h"
#include "HPFilt.h"

enum { PARAM_EXH_SS1=0,			
	   PARAM_EXH_SS2,			
	   PARAM_EXH_SS3,			
	   PARAM_EXH_SS4,					
	   PARAM_EXH_SS1k1,			
	   PARAM_EXH_SS2k1,			
	   PARAM_EXH_SS3k1,			
	   PARAM_EXH_SS4k1,					
	   PARAM_EXH_GESLAENGE,
	   PARAM_EXH_TUBE_GAIN,	
	   PARAM_EXH_TUBE_CUTOFF,	
	   PARAM_EXH_TUBE_ORDER,
	   PARAM_EXH_ENDFB_GAIN,	
	   PARAM_EXH_ENDFB_CUTOFF,	
	   PARAM_EXH_ENDFB_ORDER,
	   PARAM_EXH_METAL,			
	   PARAM_EXH_GAIN };

class Exhaust {
		
	public:	
	
		Exhaust();
		~Exhaust();
		
		void process(SIGNAL input);		

		SIGNAL lastOutL;
		SIGNAL lastOutR;
		SIGNAL intercooler;

		float supercharge;

		ExhaustParams *params;
		perfWaveGuide *myWaveguide;

	private:

		void setPipes();

		Resonator* exreso1;
		Noise* exnoise1;
		Noise* cooler_noise;
		Noise *popOffNoise;

		LPFilt *turbolp;
		HPFilt *pophp;

};
