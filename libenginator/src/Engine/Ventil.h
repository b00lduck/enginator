#pragma once
#include "vss_stdinc.h"
#include "EnginePart.h"

#define LIFT_TABLE_LEN 5000 

class Ventil : public EnginePart {

	public:
		Ventil(float open, float close, float sharpness, float Qmax, Engine* parent);
		
		void setOpen(float open);
		void setClose(float close);
		void setQmax(float Qmax);
		void setSharpness(float sharpness);
		void setPhases();
		void setTiming(float start, float stop);
		void process(float dp);

		inline float getFlow(float pos);

		float setdP(float dp);
	
		float K;
		float Qmax;
	
	private:
		float sharpness;
		float open,close;
		float basicLiftTable[LIFT_TABLE_LEN];
		float liftTable[LIFT_TABLE_LEN];
		void calcBasicLiftTable();

};