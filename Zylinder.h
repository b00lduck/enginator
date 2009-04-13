#pragma once
#include "EnginePart.h"

class Zylinder : public EnginePart {

	public:
	
	Zylinder(float hub, float bohrung, float verdichtung,float pleuel_l, float desachs,
			 float in_del, float ex_del, Engine* parent);

	void process(float dp);
	void undicht(float dp);

	void setP(float pfac);
	void setV(float newV);
	void setT(float newT);

	float setdPin(float dp);
	float setdPout(float dp);

	float V,P,Cin,Cout;
	float Pold;

	float burn,cam;

	float hub,bohrung,verdichtung,hubraum;
	float pleuel_l,desachs;

	float gasmenge,T,kolbflaeche;

	float x;	// kolbenposition

	bool ignition;

	int burntime;

};


