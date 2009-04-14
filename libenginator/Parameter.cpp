#include "Parameter.h"

Parameter::Parameter(char* name,float value,float delta,float down, float up) {

	this->name = name;
	this->delta = delta;
	this->up = up;
	this->down = down;
	this->dragmode = false;

	setValue(value);
}

void Parameter::setValue(float v) {
	value = v;
	if (value > up) value = up;
	if (value < down) value = down;			
	pct = (value - down) / (up-down); 
}

float Parameter::getValue() {
	return value;
}

int Parameter::getKnobPos(int left, int right) {
	return left + (right - left) * pct;
}

void Parameter::unClick() {
	dragmode = false;
}

void Parameter::draw(HDC hdc, RECT* rt) {

	char text[100];

	// Draw text (name)
	DrawText( hdc, name, strlen(name), rt, DT_LEFT );
	sprintf(text,"%.5f",value);
	rt->left += 100;

	// Draw text (value)
	DrawText( hdc, text, strlen(text), rt, DT_LEFT );
	rt->left += 50;		

	// clear slider area
	RECT clear;
	clear.left = rt->left - KNOBWIDTH/2;
	clear.right = rt->right + KNOBWIDTH/2;
	clear.top = rt->top;
	clear.bottom = rt->bottom;	
	FillRect(hdc, &clear, (HBRUSH) (COLOR_WINDOW+1));

	// Draw slider background
	Rectangle(hdc,rt->left,rt->top+8,rt->right,rt->bottom-10);

	// Draw slider knob
	int sliderpos = getKnobPos(rt->left,rt->right);
	Rectangle(hdc,sliderpos - KNOBWIDTH/2,rt->top+2,sliderpos+KNOBWIDTH/2,rt->bottom-4);
	if (dragmode) {
		RECT fill;
		fill.left = sliderpos - KNOBWIDTH/2;
		fill.top = rt->top+2;
		fill.right = sliderpos+KNOBWIDTH/2;
		fill.bottom = rt->bottom-4;
		FillRect(hdc, &fill, (HBRUSH) (COLOR_WINDOW+2));
	}
}
