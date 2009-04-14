#pragma once
#include "vss_stdinc.h"

class Limiter {

	public:

		Limiter(float thresh,float tatt,float trel);
		~Limiter();

		void tick(SIGNAL *inputL, SIGNAL *inputR);

		float gain;
		float env;

	private:
		
        float thresh;  // threshold 
		float scalar_rel;
		float scalar_att;

};




