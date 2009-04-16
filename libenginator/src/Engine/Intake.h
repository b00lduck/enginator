#pragma once
#include "vss_stdinc.h"
#include "IntakeSettings.h"
#include "perfWaveGuide.h"

enum { PARAM_INT_SS1=0,			
	   PARAM_INT_SS2,			
	   PARAM_INT_SS3,			
	   PARAM_INT_SS4,			
	   PARAM_INT_SS1k1,			
	   PARAM_INT_SS2k1,			
	   PARAM_INT_SS3k1,			
	   PARAM_INT_SS4k1,				
	   PARAM_INT_GESLAENGE,
	   PARAM_INT_TUBE_GAIN,	
	   PARAM_INT_TUBE_CUTOFF,	
	   PARAM_INT_TUBE_ORDER,
	   PARAM_INT_ENDFB_GAIN,	
	   PARAM_INT_ENDFB_CUTOFF,	
	   PARAM_INT_ENDFB_ORDER,
	   PARAM_INT_GAIN,
	   PARAM_INT_TUBE_NOISE };

class Intake {

	public:	
	
		Intake();
		~Intake();
		
		void process(SIGNAL input);		

		SIGNAL lastOutL,lastOutR;

		IntakeSettings *params;
		perfWaveGuide *myWaveguide;
	
	private:
		void setPipes();

};
