#pragma once
#include "vss_stdinc.h"
#include "DelayLine.h"

class floatDelayLine {

	public:

		floatDelayLine(DWORD len);
		~floatDelayLine();

		DelayLine *delay1;
		DelayLine *delay2;

		void setLen(int len);

		void advance();

};