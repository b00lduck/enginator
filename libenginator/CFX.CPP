#include "CFX.h"


CFX::CFX () {
	lastOutput[0] = lastOutput[1] = 0;
	effectMix = 0.5;
}

void CFX::tick_mono(float *pDataIn, float *pDataOut, DWORD length) {
  while(length--)
		*(pDataOut++) += (lastOutput[0] + lastOutput[1]) * 0.5f;
}

void CFX::tick_stereo(float* pDataIn, float* pDataL, float* pDataR, DWORD length) {
  while(length--) {
		tick(*(pDataIn++));
		*(pDataL++) += lastOutput[0];
		*(pDataR++) += lastOutput[1];
  }
}

bool CFX::isPrime(int number) {
  if (number == 2) return true;
  if (number & 1)	{
	  for (int i=3; i<(int)sqrt((float)number)+1; i+=2)
		  if ((number % i) == 0) return false;
	  return true;
	}
  else return false;
}