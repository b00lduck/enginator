#pragma once
#include "vss_stdinc.h"
#include "stk.h"

class lossyDelay : protected Delay {
	public:
		lossyDelay();
		lossyDelay(long theDelay, long maxDelay, float loss_factor);
		void setLoss_factor(float loss_factor);
		float tick(float sample);

	protected:
		float loss_factor;
};