#pragma once
#include "vss_stdinc.h"

#define MAXPARAMS 100

class Params {

	public:

		Params();

		void draw(HDC hdc,int x, int y);
		void click(int x, int y, int cx, int cy, int v);
		void addParam(char* name,float value,float delta,float up, float down);

		virtual void callbackSet(int p) = 0;

		void load(char* filename);
		void save(char* filename);

		bool changed;

		int numparams;

		float params[MAXPARAMS];
		float up[MAXPARAMS];
		float down[MAXPARAMS];
		char *names[MAXPARAMS];
		float delta[MAXPARAMS];
		float pct[MAXPARAMS];
		bool dragmode[MAXPARAMS];

		int getKnobPos(int left, int right, int i);

		void move(int x, int y, int mx, int my);
		void setParam(int i,float v);
		void unClick(void);
		float getPctByPos(int left, int right, int x, int i);

};