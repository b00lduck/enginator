#include "Limiter.h"

Limiter::Limiter(float thresh, float tatt, float trel) {
	scalar_rel = pow( 0.5, 1.0/(trel * (float)SAMPLERATE));
	scalar_att = pow( 0.5, 1.0/(tatt * (float)SAMPLERATE));
  env = 0.01;
	this->thresh = thresh;
}

Limiter::~Limiter() {}

void Limiter::tick(SIGNAL *inputL,SIGNAL *inputR) {

	double absvalL,absvalR,absval;

	if ((*inputL) < 0) absvalL = -(*inputL);
	else absvalL = (*inputL);

	if ((*inputR) < 0) absvalR = -(*inputR);
	else absvalR = (*inputL);

	if (absvalR > absvalL) absval = absvalR;
	else absval = absvalL;
	
	if ( absval >= env )	{
		env *= 1.01;
	} else {
		env *= 0.9999;
		if( env < VERY_SMALL_FLOAT ) env = 0.0;
	}

	if ( env < thresh ) gain = 1;
	else gain = (thresh/env);

	(*inputL) *= gain;
	(*inputR) *= gain;

}


	



