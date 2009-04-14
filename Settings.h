#pragma once
#include "vss_stdinc.h"
#include "Parameter.h"

#define MAXPARAMS 100

class Settings {

	public:

		Settings();

		void draw(HDC hdc,int x, int y);
		void click(int x, int y, int cx, int cy, int v);
		void addParam(char* name,float value,float delta,float up, float down);

		virtual void callbackSet(int p) = 0;

		void load(char* filename);
		void save(char* filename);

		bool changed;

		int numparams;

		Parameter* parameter[MAXPARAMS];

		float getParameter(int id);

		void move(int x, int y, int mx, int my);
		void setParam(int i,float v);
		void unClick(void);

	private:

		float getPctByPos(int left, int right, int x);
};