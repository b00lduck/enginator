#include "Ventil.h"

Ventil::Ventil(float open, float close, float sharpness, float Qmax, Engine* parent) : EnginePart(parent) {
	setOpen(open);
	setClose(close);
	setPhases();
	setQmax(Qmax);
	setSharpness(sharpness);
}

void Ventil::setOpen(float open) {
	this->open = open;
}

void Ventil::setClose(float close) {
	this->close = close;
}

void Ventil::setQmax(float Qmax) {
	this->Qmax = Qmax;
}

void Ventil::setSharpness(float sharpness) {
	this->sharpness = sharpness;	
	this->olen = 1 / (sharpness * 2.0f);
}

void Ventil::setPhases() {
	if (close < open) close += 720.0f;
	open_ph = (open / 720.0f) * 4 * PI;
	close_ph = (close / 720.0f) * 4 * PI;
	duration = close_ph - open_ph;
}

inline float Ventil::getFlow(float pos) {
	if (pos < olen) return sin(pos*sharpness*PI)*Qmax;
	if (pos < (1-olen)) return Qmax;
	return cos((pos - (1-olen)) * PI * sharpness)*Qmax;
}

void Ventil::process(float dp) {

	float pos;
	if (close_ph < PI4) {
		if ((phase > open_ph) && (phase <= close_ph)) {
			pos = ((phase - open_ph) / duration);
			K=getFlow(pos);
		} else K=0;
	} else {
		if (phase > open_ph) {
			pos = ((phase - open_ph) / duration);
			K=getFlow(pos);
		} else if (phase+PI4 <= close_ph) {
			pos = 1-((close_ph - (phase+PI4)) / duration);
			K=getFlow(pos);			
		} else K=0;
	}
}
