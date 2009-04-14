#pragma once
#include "vss_stdinc.h"

#define KNOBWIDTH 6

class Parameter {

	public:
		Parameter(char* name,float value,float delta,float up, float down);

		float value;
		float up;
		float down;
		char *name;
		float delta;
		float pct;
		bool dragmode;

		void setValue(float v);

		int getKnobPos(int left, int right);

		void unClick();
		void draw(HDC hdc, RECT* rt);
		float getValue();

};