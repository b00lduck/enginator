#include "lossyDelay.h"


lossyDelay::lossyDelay() : Delay() {
	loss_factor = 1;
}

lossyDelay :: lossyDelay(long theDelay, long maxDelay, float loss_factor) : Delay(theDelay, maxDelay) {
	this->loss_factor = loss_factor;
}
  
void lossyDelay :: setLoss_factor(float loss_factor) {
	this->loss_factor = loss_factor;
}

float lossyDelay :: tick(float sample) {
	return sample * loss_factor;
	return Delay::tick(sample) * loss_factor;
}


