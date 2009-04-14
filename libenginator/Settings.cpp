#include "Settings.h"

Settings::Settings() {
	numparams = 0;
}

void Settings::addParam(char* name,float value,float delta,float down, float up) {
	parameter[numparams] = new Parameter(name,value,delta,down,up);
	numparams++;
} 

float Settings::getParameter(int id) {
	return parameter[id]->value;
}

void Settings::load(char *filename) {  
	FILE *fh = fopen(filename,"r");
	if (fh) {
		int i;
		for(i=0;i<numparams;i++) {
			float v;
			fread(&v,sizeof(float),1,fh);
			parameter[i]->setValue(v);
		}
		fclose(fh);
//		changed=true;
	}
}

void Settings::save(char *filename) {
	FILE *fh = fopen(filename,"w+");
	int i;
	for(i=0;i<numparams;i++) {
		float v = parameter[i]->getValue();
		fwrite(&v,sizeof(float),1,fh);
	}
	fclose(fh);
}

void Settings::move(int x, int y, int mx, int my) {

	for (int i=0;i<numparams;i++) {
		if (parameter[i]->dragmode) {
			float p = getPctByPos(x+150,x+240,mx);
			float val = (parameter[i]->up - parameter[i]->down) * p + parameter[i]->down;
			setParam(i,val);
			i=numparams; // end loop
		}
	}
}

void Settings::click(int x, int y, int cx, int cy, int v) {

	RECT rt;

	rt.left = x;
	rt.right = x + 240;
	rt.top = y;
	rt.bottom = y + 22;	
	
	for (int i=0;i<numparams;i++) {
		rt.left += 150;		
		if ((rt.left <= cx) && (rt.right >= cx) && (rt.top <= cy) && (rt.bottom >= cy))	{

			int kp = parameter[i]->getKnobPos(rt.left,rt.right);
			int kl = kp - KNOBWIDTH / 2;
			int kr = kp + KNOBWIDTH / 2;

			if ((kl <= cx) && (kr >= cx)) {
				parameter[i]->dragmode = !(parameter[i]->dragmode);
			} else {
				float v1 = parameter[i]->value + parameter[i]->delta * (float)v;
				setParam(i,v1);
			}
		}
		rt.left -= 150;
		rt.top += 22; rt.bottom += 22;
	}		
}

void Settings::setParam(int i,float v) {
	parameter[i]->setValue(v);
	callbackSet(i);
}

float Settings::getPctByPos(int left, int right, int x) {
	return ((float)x - (float)left) / ((float)right - (float)left); 
}

void Settings::unClick() {
	for (int i=0;i<numparams;i++) {
		parameter[i]->unClick();
	}
}

void Settings::draw(HDC hdc, int x, int y) {

	RECT rt;
	rt.left = x;
	rt.right = x + 240;
	rt.top = y;
	rt.bottom = y + 22;	
	
	for (int i=0;i<numparams;i++) {
		parameter[i]->draw(hdc, &rt);
		rt.left -= 150;
		rt.top += 22; rt.bottom += 22;
	}
}