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
	P = 0;				// Zylinderinnendruck / kpa
	x = 0;				// Kolbenposition / m
	verdichtung = 7;	// verdichtung 1 zu 7
	gasmenge = 0;		// Gasmenge / kg
	T = 300.0f;			// t / Kelvin
	Cin = 100;			// Gegendruck / kpa
	Cout = 100;			// Gegendruck / kpa	

	Pold = 0;

	kolbflaeche = bohrung*bohrung*PI/4.0f;

	burntime = 0;

	ignition = true;

}

void Zylinder::setP(float newp) {
	P = newp;
	gasmenge = V * P /( T * 287.0f);
}

float Zylinder::setdPin(float dp) {
	float t = P-Cin;
	float dp1 = 0;
	if (t>0) dp1 = sqrt(t) * dp;
	else dp1 = -sqrt(-t) * dp;
	P -= dp1;
	gasmenge = V * P /( T * 287.0f);
	return dp1;
}

float Zylinder::setdPout(float dp) {
	float t = P-Cout;
	float dp1 = 0;
	if (t>0) dp1 = sqrt(t) * dp;
	else dp1 = -sqrt(-t) * dp;
	P -= dp1;
	gasmenge = V * P /( T * 287.0f);
	  if ((phase > 6) && (phase <= 6.3)) {
		return dp1 * 5.0;
	  } else {
		return dp1;
	  }
}

void Zylinder::setV(float newV) {
	V = newV;
	P = (gasmenge / V) * (T * 287.0f);
}

void Zylinder::setT(float newT) {
	T = newT;
	P = (gasmenge / V) * (T * 287.0f);
}


void Zylinder::process(float dp) {

	#define ign_start	(PI2)			
	#define ign_stop	(PI2+0.1)			
	
	float tmp = ( (sin(phase) * hub / (2.0f*pleuel_l)) - desachs / pleuel_l);
	x = (hub / 2.0f) * (1.0f - cos(phase)) + pleuel_l * ( 1.0f - sqrt(1-(tmp*tmp)));
	V = (hub * kolbflaeche) / (verdichtung-1.0f) + kolbflaeche * x;
	setV(V);

	// Zündung !
	if (parent->ignition) {
		if (burntime == 0) {
			if ((phase > ign_start) && (phase <= ign_stop)) {				
				
				setT(287+1500);

				if ((parent->throttle < 0.4)) {
					int r=rand();
					if (r < (1300 / parent->cyls)) setT(287);
					if ((parent->throttle < 0.05) &&
						//(parent->rpm > (limiter * 0.25)) && 
						//(parent->rpm < (limiter * 0.75)) &&
						(r < (800 / parent->cyls))) setT(287+90*r);					
				}
		
			}
		} else {
			burntime--;
		}
	}
	// Auspuffen
	if ((phase > 0) && (phase <= 0.1)) setT(287);

	Pold = P;
}



