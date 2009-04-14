#pragma once
#include "vss_stdinc.h"

class FIR {

	public:

		FIR();
		~FIR();

		void setLowpass(int len, float cutoff, float gain);

		float tick(float input);

	private:
		
		float *buffer;
		float *buffer1;
		float *Coef;

		DWORD Order;

		void deleteAll();

		DWORD CoefNum;
		DWORD datasize;
		int in_pointer;
};




