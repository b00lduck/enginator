#pragma once
#include "vss_stdinc.h"

class CFilter {

  public:
		CFilter();
	    void Reset();
		float tick(float in);
		void Set(float freq, float res, float vol);
		float vol;
 
  private:

		float freq;
		float R,g;
		float omega;

		float xn,xn1,xn2;
		float yn,yn1,yn2;

};




