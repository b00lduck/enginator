#pragma once
#include "vss_stdinc.h"
#include "EnginePart.h"

class Ventil : public EnginePart {

	public:
		Ventil(float open, float close, float sharpness, float Qmax, Engine* parent);
		
		void setOpen(float open);
		void setClose(float close);
		void setQmax(float Qmax);
		void setSharpness(float sharpness);
		void setPhases();

		void process(float dp);

		inline float getFlow(float pos);

		float open,close;

		float setdP(float dp);

		float K;
		
		float olen;
		float duration;

		float Qmax;
		float open_ph,close_ph,sharpness;
};