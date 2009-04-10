#include "Params.h"

#define KNOBWIDTH 6

Params::Params() {
	numparams = 0;
}

void Params::addParam(char* name,float value,float delta,float down, float up) {
	this->params[numparams] = value;
	this->names[numparams] = name;
	this->delta[numparams] = delta;
	this->up[numparams] = up;
	this->down[numparams] = down;	
	this->pct[numparams] = (value-down) / (up-down); 
	this->dragmode[numparams] = false;
	numparams++;
} 

void Params::load(char *filename) {  
	FILE *fh = fopen(filename,"r");
	if (fh) {
		fread(params,sizeof(params),1,fh);
		fclose(fh);  
		changed=true;
	}
	int i;
	for(i=0;i<numparams;i++) {
		pct[i] = (params[i] - down[i]) / (up[i]-down[i]); 	
	}
}

void Params::save(char *filename) {
  FILE *fh = fopen(filename,"w+");
  fwrite(params,sizeof(params),1,fh);
  fclose(fh);
}

void Params::move(int x, int y, int mx, int my) {

	for (int i=0;i<numparams;i++) {
		if (dragmode[i]) {
			float p = getPctByPos(x+150,x+240,mx,i);
			float val = (up[i] - down[i]) * p + down[i];
			setParam(i,val);
			i=numparams; // end loop
		}
	}
}

void Params::click(int x, int y, int cx, int cy, int v) {

	RECT rt;

	rt.left = x;
	rt.right = x + 240;
	rt.top = y;
	rt.bottom = y + 22;	
	
	for (int i=0;i<numparams;i++) {
		rt.left += 150;		
		if ((rt.left <= cx) && (rt.right >= cx) && (rt.top <= cy) && (rt.bottom >= cy))	{

			int kp = getKnobPos(rt.left,rt.right,i);
			int kl = kp - KNOBWIDTH / 2;
			int kr = kp + KNOBWIDTH / 2;

			if ((kl <= cx) && (kr >= cx)) {
				this->dragmode[i] = !(this->dragmode[i]);
			} else {
				float v1 = params[i] + delta[i] * (float)v;
				setParam(i,v1);
			}
		}
		rt.left -= 150;
		rt.top += 22; rt.bottom += 22;
	}		
}

void Params::setParam(int i,float v) {
	params[i] = v;
	if (params[i] > up[i]) params[i] = up[i];
	if (params[i] < down[i]) params[i] = down[i];			
	pct[i] = (params[i] - down[i]) / (up[i]-down[i]); 
	callbackSet(i);
}

int Params::getKnobPos(int left, int right, int i) {
   return left + (right - left) * this->pct[i];
}

float Params::getPctByPos(int left, int right, int x, int i) {
   return ((float)x - (float)left) / ((float)right - (float)left); 
}


void Params::unClick() {
	for (int i=0;i<numparams;i++) {
		dragmode[i] = false;
	}
}

void Params::draw(HDC hdc, int x, int y) {

	RECT rt;

	char text[100];

	rt.left = x;
	rt.right = x + 240;
	rt.top = y;
	rt.bottom = y + 22;	
	
	for (int i=0;i<numparams;i++) {
		// Draw text (name)
		DrawText( hdc, names[i], strlen(names[i]), &rt, DT_LEFT );
		sprintf(text,"%.5f",params[i]);
		rt.left += 100;

		// Draw text (value)
		DrawText( hdc, text, strlen(text), &rt, DT_LEFT );
		rt.left += 50;		

		// clear slider area
		RECT clear;
		clear.left = rt.left - KNOBWIDTH/2;
		clear.right = rt.right + KNOBWIDTH/2;
		clear.top = rt.top;
		clear.bottom = rt.bottom;	
		FillRect(hdc, &clear, (HBRUSH) (COLOR_WINDOW+1));

		// Draw slider background
		Rectangle(hdc,rt.left,rt.top+8,rt.right,rt.bottom-10);
	
		// Draw slider knob
		int sliderpos = getKnobPos(rt.left,rt.right,i);
		Rectangle(hdc,sliderpos - KNOBWIDTH/2,rt.top+2,sliderpos+KNOBWIDTH/2,rt.bottom-4);
		if (dragmode[i]) {
			RECT fill;
			fill.left = sliderpos - KNOBWIDTH/2;
			fill.top = rt.top+2;
			fill.right = sliderpos+KNOBWIDTH/2;
			fill.bottom = rt.bottom-4;
			FillRect(hdc, &fill, (HBRUSH) (COLOR_WINDOW+2));
		}
		rt.left -= 150;
		rt.top += 22; rt.bottom += 22;
	}
}