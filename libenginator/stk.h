#pragma once
#include "vss_stdinc.h"

class Filter {
	public:
		Filter(void);
		Filter(int nb, float *bCoefficients, int na, float *aCoefficients);
		virtual ~Filter(void);
		void clear(void);
		void setCoefficients(int nb, float *bCoefficients, int na, float *aCoefficients);
		void setNumerator(int nb, float *bCoefficients);
		void setDenominator(int na, float *aCoefficients);
		virtual void setGain(float theGain);
		virtual float getGain(void) const;
		virtual float lastOut(void) const;
		virtual float tick(float sample);
		virtual float *tick(float *vector, unsigned int vectorSize);

	protected:
		float gain;
		int   nB;
		int   nA;
		float *b;
		float *a;
		float *outputs;
		float *inputs;
};

class Delay : protected Filter {
	public:
		Delay();
		Delay(long theDelay, long maxDelay);
		virtual ~Delay();
		void clear();
		void setDelay(long theDelay);
		void setMaximumDelay(long maxDelay);
		long getDelay(void) const;
		float energy(void) const;
		float contentsAt(long tapDelay) const;
		float lastOut(void) const;
		virtual float nextOut(void) const;
		virtual float tick(float sample);
		virtual float *tick(float *vector, unsigned int vectorSize);

	protected:
		long inPoint;
		long outPoint;
		long length;
		float delay;
};

class DelayL : public Delay {
	public:
		DelayL();
		DelayL(float theDelay, long maxDelay);
		void setDelay(float theDelay);
		float getDelay(void) const;
		float nextOut(void);
		float tick(float sample);

	protected:  
		float alpha;
		float omAlpha;
		float nextOutput;
		bool doNextOut;
};

class Reverb {
	public:
		Reverb();
		virtual void clear() = 0;
		float lastOut() const;
		float lastOutLeft() const;
		float lastOutRight() const;
		virtual float tick(float input) = 0;
		virtual float *tick(float *vector, unsigned int vectorSize);
		void tick_stereo(float* pDataIn, float* pDataL, float* pDataR, DWORD length);

	protected:	  
		bool isPrime(int number);
		float lastOutput[2];

};
