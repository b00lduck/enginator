#include "Ventil.h"

Ventil::Ventil(float open, float close, float sharpness, float Qmax, Engine* parent) : EnginePart(parent) {
	setOpen(RAD(open));
	setClose(RAD(close));
	setQmax(Qmax);
	calcLiftTable();
}

void Ventil::calcLiftTable() {
	memset(liftTable,0,sizeof(liftTable));

	float liftTablePhaseStep = FOUR_PI / (float)LIFT_TABLE_LEN;
	float phase = 0;

	float sinPhase = 1.5 * PI; // start is the low of the sinecurve (3/2 PI) 
	float sinPhaseStep = (close-open) / FOUR_PI;
	sinPhaseStep = liftTablePhaseStep / (sinPhaseStep * 2); 

	int i;
	for(i=0;i<LIFT_TABLE_LEN;i++) {

		if ((phase >= open) && (phase <= close)) {
			float v = (sin(sinPhase) + 1) / 2.0f;
			liftTable[i] = v;
			sinPhase += sinPhaseStep;		
		}
		phase += liftTablePhaseStep;
	
	}

}

void Ventil::setOpen(float open) {
	this->open = open;
}

void Ventil::setClose(float close) {
	this->close = close;
}

void Ventil::setQmax(float Qmax) {
	this->Qmax = Qmax;
}

float Ventil::getLift() {
	//return 1;
	float f = int(LIFT_TABLE_LEN * phase / FOUR_PI);
	int lti = floor(f);
	LTIe = lti;
	if (lti < LIFT_TABLE_LEN) {
		return liftTable[lti];
	} else {
		return 0;
	}
}

void Ventil::process(float dp) {
	K = getLift() * Qmax;
	return;

/*	int lti = 720.0 * phase / FOUR_PI;
	K = liftTable[lti];
	return;

	if ((phase > open_ph) && (phase <= close_ph)) {
		K = Qmax;
	} else {
		K = 0;
	}
	return;

	float pos;
	if (close_ph < PI4) {
		if ((phase > open_ph) && (phase <= close_ph)) {
			pos = ((phase - open_ph) / duration);
			K = getFlow(pos);
		} else K=0;
	} else {
		if (phase > open_ph) {
			pos = ((phase - open_ph) / duration);
			K = getFlow(pos);
		} else if (phase+PI4 <= close_ph) {
			pos = 1-((close_ph - (phase+PI4)) / duration);
			K = getFlow(pos);			
		} else K = 0;
	}
*/
}
