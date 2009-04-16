#include "Ventil.h"
#include "Engine.h"
#include "Intake.h"

Ventil::Ventil(float open, float close, float sharpness, float Qmax, Engine* parent) : EnginePart(parent) {
	setQmax(Qmax);
	setTiming(open,close);
	calcBasicLiftTable();
	setSharpness(sharpness);
}

void Ventil::setSharpness(float sharpness) {
	this->sharpness = sharpness;
	int i;
	for(i=0;i<LIFT_TABLE_LEN;i++) {
		liftTable[i] = pow(basicLiftTable[i], 1.0f/sharpness);
	}
	
}

void Ventil::setTiming(float start, float stop) {
	setOpen(RAD(start));
	setClose(RAD(stop));
	calcBasicLiftTable();
	setSharpness(sharpness);
}

void Ventil::calcBasicLiftTable() {

	memset(liftTable,0,sizeof(liftTable));
	memset(basicLiftTable,0,sizeof(basicLiftTable));
	

	float liftTablePhaseStep = FOUR_PI / (float)LIFT_TABLE_LEN;
	float phase = 0;

	float sinPhase = 1.5 * PI; // start is the low of the sinecurve (3/2 PI) 
	float sinPhaseStep = (close-open) / FOUR_PI;
	sinPhaseStep = liftTablePhaseStep / (sinPhaseStep * 2); 

	int i;
	for(i=0;i<LIFT_TABLE_LEN;i++) {

		if ((phase >= open) && (phase <= close)) {
			float v = (sin(sinPhase) + 1) / 2.0f;
			basicLiftTable[i] = v;
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

void Ventil::process(float dp) {
	float f = (LIFT_TABLE_LEN-1) * phase / FOUR_PI;
	
	int lti = floor(f);
	float frac = f - lti;	
	
	if (lti < (LIFT_TABLE_LEN-1)) {
		// linear interpolation
		K = (liftTable[lti] * (1-frac)) + (liftTable[lti+1] * frac);
		K *= Qmax;
	} else {
		K = 0;
	}

}
