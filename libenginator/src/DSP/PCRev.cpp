#include "PCRev.h"

PRCRev :: PRCRev(float T60, float mix = 0.5) {
  // Delay lengths for 44100 Hz sample rate.
  int lengths[4]= {353, 1097, 1777, 2137};

  int delay, i;

  for (i=0; i<2; i++)	{
	allpassDelays[i].setMaximumDelay( lengths[i] );
	allpassDelays[i].setDelay( lengths[i] );

    combDelays[i].setMaximumDelay( lengths[i+2] );
    combDelays[i].setDelay( lengths[i+2] );
  }

  this->setT60( T60 );
  allpassCoefficient = 0.7;
  effectMix = mix;
  this->clear();
}

PRCRev :: ~PRCRev(){
}

void PRCRev :: clear() {
  allpassDelays[0].clear();
  allpassDelays[1].clear();
  combDelays[0].clear();
  combDelays[1].clear();
  lastOutput[0] = 0.0;
  lastOutput[1] = 0.0;
}

void PRCRev :: setT60( float T60 ) {
  combCoefficient[0] = pow(10.0, (-3.0 * combDelays[0].getDelay() / (T60 * SAMPLERATE)));
  combCoefficient[1] = pow(10.0, (-3.0 * combDelays[1].getDelay() / (T60 * SAMPLERATE)));
}

void PRCRev :: tick(float input) {
  float temp, temp0, temp1, temp2, temp3;

  temp = allpassDelays[0].lastOut();
  temp0 = allpassCoefficient * temp;
  temp0 += input;
  allpassDelays[0].tick(temp0);
  temp0 = -(allpassCoefficient * temp0) + temp;
    
  temp = allpassDelays[1].lastOut();
  temp1 = allpassCoefficient * temp;
  temp1 += temp0;
  allpassDelays[1].tick(temp1);
  temp1 = -(allpassCoefficient * temp1) + temp;
    
  temp2 = temp1 + (combCoefficient[0] * combDelays[0].lastOut());
  temp3 = temp1 + (combCoefficient[1] * combDelays[1].lastOut());

  lastOutput[0] = effectMix * (combDelays[0].tick(temp2));
  lastOutput[1] = effectMix * (combDelays[1].tick(temp3));
  temp = (1.0 - effectMix) * input;
  lastOutput[0] += temp;
  lastOutput[1] += temp;   
}