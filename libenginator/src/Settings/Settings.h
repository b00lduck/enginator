#pragma once
#include "vss_stdinc.h"
#include "Parameter.h"

#define MAXPARAMS 100

class Settings {

	public:
		Settings();


		void addParam(char* name,float value,float delta,float up, float down);

		virtual void callbackSet(int p) = 0;

		void load(char* filename);
		void save(char* filename);

		bool changed;

		int numparams;

		Parameter* parameter[MAXPARAMS];

		float getParameter(int id);

		
		void setParam(int i,float v);

		void draw(HDC hdc);
		void click(int cx, int cy);
		void move(int mx, int my);
		void unclick();

	protected:

		int xpos,ypos;

	private:

		float getPctByPos(int left, int right, int x);

};