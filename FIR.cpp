#include "FIR.h"

// http://homepages.which.net/~paul.hills/Circuits/MercurySwitchFilter/FIR.html

FIR::FIR() {
	Coef = NULL;
	buffer = NULL;
	buffer1 = NULL;
	CoefNum = 0;
}

FIR::~FIR() {
}

void FIR::deleteAll() {
	SAFE_DELETE(Coef);
	SAFE_DELETE(buffer);
	SAFE_DELETE(buffer1);
}

void FIR::setLowpass(int len, float cutoff, float gain) {

	deleteAll();

	double Sum, TmpFloat;
	int CoefNum, HalfLen, Cnt;

	CoefNum = len;
	if (len % 2 == 0) CoefNum++;

	HalfLen = (CoefNum - 1) / 2;
	Order = CoefNum;

	Coef = new float[CoefNum];   ZeroMemory(Coef,sizeof(float)*CoefNum);
	buffer = new float[CoefNum]; ZeroMemory(buffer,sizeof(float)*CoefNum);
	buffer1 = new float[CoefNum-1]; ZeroMemory(buffer1,sizeof(float)*(CoefNum-1));
	
	// Calculate coeff
	Coef[HalfLen] = cutoff;
	for (Cnt=1; Cnt<=HalfLen; Cnt++) {
		TmpFloat = PI * Cnt;
		Coef[HalfLen + Cnt] = sin(cutoff * TmpFloat) / TmpFloat;
		Coef[HalfLen - Cnt] = Coef[HalfLen + Cnt];
	}

	TmpFloat = 2.0 * PI / (CoefNum - 1.0);
	Sum = 0.0;
	for (Cnt=0; Cnt<CoefNum; Cnt++) {
		Coef[Cnt] *= (0.54 - 0.46 * cos(TmpFloat * Cnt));
		Sum += Coef[Cnt];
	}

	// Normalize Coeff
	for (Cnt=0; Cnt<CoefNum; Cnt++) {
		Coef[Cnt] /= fabs (Sum);
		Coef[Cnt] *= gain;
	}

	datasize = sizeof(float)*(Order-1);
	
}


float FIR::tick(float input) {

	int Cnt;

	float output = 0;

	// copy buffer
	for (Cnt=Order-1; Cnt>0; Cnt--) {
		buffer[Cnt] = buffer[Cnt-1];
	}

	// copy buffer1
//	memcpy(buffer1,buffer,datasize);
//	memcpy(buffer+sizeof(float),buffer1,datasize);

	buffer[0] = input;

	for (Cnt=0; Cnt<Order; Cnt++) {
		output += buffer[Cnt] * Coef[Cnt];
	}

	return output;
}



