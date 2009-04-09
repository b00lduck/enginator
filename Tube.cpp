#include "Tube.h"

Tube::Tube( DWORD len, float noisefac, float k, float co, float ord) : ChainElement() {

	delay = new floatDelayLine(len);
	setLen(len);
	filt1 = new LPFilt(co,k,ord);
	filt2 = new LPFilt(co,k,ord);
	noise1 = new Noise();
	noise2 = new Noise();
	this->noisefac = noisefac;
}


Tube::~Tube() {
	delete(delay);
	delete(filt1);
	delete(filt2);
	delete(noise1);
	delete(noise2);
}


void Tube::setLen(float len) {
	this->len = len;
	delay->setLen(len);
}

void Tube::setup() {}

void Tube::transform()  {

	float n,m;

	n = delay->delay1->read();
	m = delay->delay2->read();

	n += noise1->tick() * n * noisefac;
	m += noise2->tick() * m * noisefac;

	b = filt1->tick(n);
	c = filt2->tick(m);

	delay->delay1->writ(a);
	delay->delay2->writ(d);
	
	delay->advance();

}