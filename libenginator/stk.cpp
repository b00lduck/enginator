#include "stk.h"

#define BOUND_MINDELAY 2
#define BOUND_MAXDELAY 30000

Reverb :: Reverb(){
}

float Reverb :: lastOut() const {
  return (float) ((lastOutput[0] + lastOutput[1]) * 0.5f);
}

float Reverb :: lastOutLeft() const {
  return lastOutput[0];
}

float Reverb :: lastOutRight() const {
  return lastOutput[1];
}

float *Reverb :: tick(float *vector, unsigned int vectorSize) {
  for (unsigned int i=0; i<vectorSize; i++) vector[i] = tick(vector[i]);
  return vector;
}

Delay :: Delay() {
  length = 4096;
  delete [] inputs;
  inputs = new float[length];
  this->clear();
  inPoint = 0;
  outPoint = 0;
  delay = 0;
}

Delay :: Delay(long theDelay, long maxDelay) {

  if ((maxDelay < BOUND_MINDELAY) || (maxDelay > BOUND_MAXDELAY)) {
	  MessageBox(NULL,"Delay::Delay boundary check failed.","Error",0);
	  exit(1);
  } else {
	this->setMaximumDelay(maxDelay);
	this->setDelay(theDelay);
  }
}

Delay :: ~Delay() {
}

void Delay :: clear(void) {
  long i;
  for (i=0;i<length;i++) inputs[i] = 0.0;
  outputs[0] = 0.0;
}

void Delay :: setDelay(long theDelay) {
  if (theDelay > length-1) {
    outPoint = inPoint + 1;
    delay = (float) (length - 1);
  } else if (theDelay < 0 ) {
    outPoint = inPoint;
    delay = 0;
  } else {
    outPoint = inPoint - (long) theDelay;  // read chases write
    delay = (float) theDelay;
  }

  while (outPoint < 0) outPoint += length;  // modulo maximum length
}

void Delay :: setMaximumDelay(long maxDelay) {
  
  length = maxDelay+1;
  delete [] inputs;
  inputs = new float[length];
  this->clear();
  inPoint = 0;
}

long Delay :: getDelay(void) const {
  return (long)delay;
}

float Delay :: energy(void) const {
  int i;
  register float e = 0;
  if (inPoint >= outPoint) {
    for (i=outPoint; i<inPoint; i++) {
      register float t = inputs[i];
      e += t*t;
    }
  } else {
    for (i=outPoint; i<length; i++) {
      register float t = inputs[i];
      e += t*t;
    }
    for (i=0; i<inPoint; i++) {
      register float t = inputs[i];
      e += t*t;
    }
  }
  return e;
}

float Delay :: contentsAt(long tapDelay) const {
  long i = tapDelay;
  if (i < 0) {
    i = 0;
  }
  else if (i > delay) {
    i = (long) delay;
  }
  long tap = inPoint - i;
  if (tap < 0) // Check for wraparound.
    tap += length;
  return inputs[tap];
}

float Delay :: lastOut(void) const {
  return Filter::lastOut();
}

float Delay :: nextOut(void) const {
  return inputs[outPoint];
}


float Delay :: tick(float sample) {
  inputs[inPoint++] = sample;
  if (inPoint == length) inPoint -= length;
  outputs[0] = inputs[outPoint++];
  if (outPoint>=length) outPoint -= length;
  return outputs[0];
}


float *Delay :: tick(float *vector, unsigned int vectorSize) {
  while (vectorSize--) *vector++ = tick(*vector);
  return vector;
}


Filter :: Filter() {
  gain = 1.0;
  nB = 1;
  nA = 1;
  b = new float[nB];
  b[0] = 1.0;
  a = new float[nA];
  a[0] = 1.0;
  inputs = new float[nB];
  outputs = new float[nA];
  this->clear();
}


Filter :: Filter(int nb, float *bCoefficients, int na, float *aCoefficients) {
  gain = 1.0;
  nB = nb;
  nA = na;
  b = new float[nB];
  a = new float[nA];
  inputs = new float[nB];
  outputs = new float[nA];
  this->clear();
  this->setCoefficients(nB, bCoefficients, nA, aCoefficients);
}


Filter :: ~Filter() {
  delete [] b;
  delete [] a;
  delete [] inputs;
  delete [] outputs;
}


void Filter :: clear(void) {
  int i;
  for (i=0; i<nB; i++) inputs[i] = 0.0;
  for (i=0; i<nA; i++) outputs[i] = 0.0;
}


void Filter :: setCoefficients(int nb, float *bCoefficients, int na, float *aCoefficients) {
  int i;
  if (nb != nB) {
    delete [] b;
    delete [] inputs;
    nB = nb;
    b = new float[nB];
    inputs = new float[nB];
    for (i=0; i<nB; i++) inputs[i] = 0.0;
  }
  if (na != nA) {
    delete [] a;
    delete [] outputs;
    nA = na;
    a = new float[nA];
    outputs = new float[nA];
    for (i=0; i<nA; i++) outputs[i] = 0.0;
  }
  for (i=0; i<nB; i++)
    b[i] = bCoefficients[i];
  for (i=0; i<nA; i++)
    a[i] = aCoefficients[i];

  // scale coefficients by a[0] if necessary
  if (a[0] != 1.0) {
    for (i=0; i<nB; i++) b[i] /= a[0];
    for (i=0; i<nA; i++) a[i] /= a[0];
  }
}


void Filter :: setNumerator(int nb, float *bCoefficients) {
  int i;
  if (nb != nB) {
    delete [] b;
    delete [] inputs;
    nB = nb;
    b = new float[nB];
    inputs = new float[nB];
    for (i=0; i<nB; i++) inputs[i] = 0.0;
  }
  for (i=0; i<nB; i++) b[i] = bCoefficients[i];
}


void Filter :: setDenominator(int na, float *aCoefficients) {
  int i;
  if (na != nA) {
    delete [] a;
    delete [] outputs;
    nA = na;
    a = new float[nA];
    outputs = new float[nA];
    for (i=0; i<nA; i++) outputs[i] = 0.0;
  }

  for (i=0; i<nA; i++) a[i] = aCoefficients[i];

  // scale coefficients by a[0] if necessary
  if (a[0] != 1.0) {
    for (i=0; i<nB; i++) b[i] /= a[0];
    for (i=0; i<nA; i++) a[i] /= a[0];
  }
}


void Filter :: setGain(float theGain) {
  gain = theGain;
}


float Filter :: getGain(void) const {
  return gain;
}


float Filter :: lastOut(void) const {
  return outputs[0];
}


float Filter :: tick(float sample) {
  int i;
  outputs[0] = 0.0;
  inputs[0] = gain * sample;
  for (i=nB-1; i>0; i--) {
    outputs[0] += b[i] * inputs[i];
    inputs[i] = inputs[i-1];
  }
  outputs[0] += b[0] * inputs[0];
  for (i=nA-1; i>0; i--) {
    outputs[0] += -a[i] * outputs[i];
    outputs[i] = outputs[i-1];
  }
  return outputs[0];
}


float *Filter :: tick(float *vector, unsigned int vectorSize) {
  for (unsigned int i=0; i<vectorSize; i++) vector[i] = tick(vector[i]);
  return vector;
}

DelayL :: DelayL() {
  doNextOut = true;
}

DelayL :: DelayL(float theDelay, long maxDelay) {
  length = maxDelay+1;
  if ( length > 4096 ) {
    delete [] inputs;
    inputs = new float[length];
    this->clear();
  }
  inPoint = 0;
  this->setDelay(theDelay);
  doNextOut = true;
}


void DelayL :: setDelay(float theDelay) {
  float outPointer;
  outPointer = inPoint - theDelay;  // read chases write
  delay = theDelay;
  while (outPointer < 0) outPointer += length; // modulo maximum length
  outPoint = (long) outPointer;  // integer part
  alpha = outPointer - outPoint; // fractional part
  omAlpha = (float) 1.0 - alpha;
}


float DelayL :: getDelay(void) const {
  return delay;
}


float DelayL :: nextOut(void) {
  if ( doNextOut ) {
    // First 1/2 of interpolation
    nextOutput = inputs[outPoint] * omAlpha;
    // Second 1/2 of interpolation
    if (outPoint+1 < length)
      nextOutput += inputs[outPoint+1] * alpha;
    else
      nextOutput += inputs[0] * alpha;
    doNextOut = false;
  }
  return nextOutput;
}


float DelayL :: tick(float sample) {
  inputs[inPoint++] = sample;  
  if (inPoint == length) inPoint -= length;
  outputs[0] = nextOut();
  doNextOut = true;
  if (++outPoint >= length) outPoint -= length;
  return outputs[0];
}