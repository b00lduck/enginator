#include "Filt.h"

Filt::Filt(float cut, float g, int ord) {

	order = ord;

	if (ord < 0) ord = 0;
	if (ord > MAXFORD) ord = 0;

	setCutoff(cut);
	setGain(g);

	buffer = new float[MAXFORD];

	ZeroMemory(buffer,sizeof(float)*MAXFORD);

}

Filt::~Filt() {
	delete(buffer);
}

void Filt::setCutoff(float newc) {
	if (newc > 1) newc = 1;
	if (newc < 0) newc = 0;

	cutoff = newc;
	cutoff_a = 1-cutoff;
}


void Filt::setGain(float g) {
	gain = g;
}