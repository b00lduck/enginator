#include "LPFilt.h"

LPFilt::LPFilt(float cut, float g, int ord) : Filt(cut,g,ord) {

}

float LPFilt::tick(float in) {
	if (order <= 0) return in * gain;

	buffer[0] = (in * cutoff) + (buffer[0] * cutoff_a);	

	for (int i=1;i<order;i++) buffer[i] = (buffer[i-1] * cutoff) + (buffer[i] * cutoff_a);	
	 	
	return buffer[order-1] * gain;
}