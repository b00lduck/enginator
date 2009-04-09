#include "IIR.h"

IIR::IIR() {
	buffer = NULL;	
	setLowpass(1,1,1);
}

IIR::~IIR() {
	SAFE_DELETE(buffer);
}

void IIR::setLowpass(int o, float c, float g) {
	SAFE_DELETE(buffer);
	buffer = new float[o];
	ZeroMemory(buffer,sizeof(float)*o);
	if (c > 1) c = 1;
	if (c < 0) c = 0;
	cutoff = c;
	cutoff_a = (1-cutoff);
	gain = g;
	order = o;
}

float IIR::tick(float in) {
	buffer[0] = (in * cutoff) + (buffer[0] * cutoff_a);	
	for (int i=1;i<order;i++) buffer[i] = (buffer[i-1] * cutoff) + (buffer[i] * cutoff_a);		 	
	return buffer[order-1] * gain;
}

float IIR::tickHP(float in) {
	buffer[0] = (in * cutoff) + (buffer[0] * cutoff_a);	
	for (int i=1;i<order;i++) buffer[i] = (buffer[i-1] * cutoff) + (buffer[i] * cutoff_a);		 	
	return (in-buffer[order-1]) * gain;
}
