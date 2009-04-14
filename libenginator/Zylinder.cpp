#include "Zylinder.h"
#include "Engine.h"

Zylinder::Zylinder(float hub, float bohrung, float verdichtung,float pleuel_l,float desachs,
				   float in_del, float ex_del, Engine* parent) : EnginePart(parent) {

	this->hub = hub;
	this->bohrung = bohrung;
	this->verdichtung = verdichtung;
	this->pleuel_l = pleuel_l;
	this->desachs = desachs;

	V = 0;				// volumen / m³
	P = UMGEBUNGSDRUCK;	// Zylinderinnendruck / kpa
	x = 0;				// Kolbenposition / m
	verdichtung = 7;	// verdichtung 1 zu 7
	gasmenge = 0;		// Gasmenge / kg
	T = 300.0f;			// t / Kelvin
	kolbflaeche = bohrung*bohrung*PI/4.0f;
	burntime = 0;
	ignition = true;
}

float Zylinder::setdP(float dp) {
	float Pdiff = P - UMGEBUNGSDRUCK;
	float dp1 = 0;
	if (Pdiff > 0) {
		dp1 = sqrt(Pdiff) * dp;
	} else {
		dp1 = -sqrt(-Pdiff) * dp;
	}
	setP(P-dp1);
	return dp1;
}

void Zylinder::setP(float newp) {
	P = newp;
	gasmenge = (V * P) /( T * GASKONSTANTE);
}

void Zylinder::setV(float newV) {
	V = newV;
	P = gasmenge * T * GASKONSTANTE / V;
}

void Zylinder::setT(float newT) {
	T = newT;
	P = gasmenge * T * GASKONSTANTE / V;
}
 
void Zylinder::process(float dp) {

	#define ign_start	(PI2)			
	#define ign_stop	(PI2+0.5)			
	
	float tmp = ( (sin(phase) * hub / (2.0f*pleuel_l)) - desachs / pleuel_l);
	x = (hub / 2.0f) * (1.0f - cos(phase)) + pleuel_l * ( 1.0f - sqrt(1-(tmp*tmp)));
	V = (hub * kolbflaeche) / (verdichtung-1.0f) + kolbflaeche * x;
	setV(V);

	// Zündung !
	if (ignition) {
		//if (burntime == 0) {
			if ((phase > ign_start) && (phase <= ign_stop)) {				
				setT(300+2500);	
		//		burntime = 5000;
		      	}
		//} else {
		//	burntime--;
		//}
	}
	// Auspuffen/ansaugen
	if ((phase > 12) || (phase <= 0.1)) setT(300);

}