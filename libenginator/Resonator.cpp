#include "Resonator.h"

Resonator::Resonator() {
	rescount = 0;
}

Resonator::~Resonator() {
	for (int i=0;i<rescount;i++) {
		delete(resos[i]);
	}
}

void Resonator::addRes(float freq, float res, float vol) {
	resos[rescount] = new CFilter();
	
	resos[rescount]->Set(freq,res,vol);
	rescount++;
}

float Resonator::tick(float in) {

	float out = 0;

	for (int i=0;i<rescount;i++) {
		out += resos[i]->tick(in);
	}

	return out;
}
