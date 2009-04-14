#pragma once
#include "vss_stdinc.h"

class DelayLine {

	public:
		DelayLine(DWORD len);
		~DelayLine();

		void writ(float in);
		float read();
		void advance();

		void clear();

		float *delay;

		DWORD length;

		int readpos;
		int writepos;

		void setLen(int len);



};