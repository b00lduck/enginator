#pragma once
#include "EnginePart.h"

#define GASKONSTANTE 250.0f
#define UMGEBUNGSDRUCK 100.0f

class Zylinder : public EnginePart {

	public:
		Zylinder(float hub, float bohrung, float verdichtung,float pleuel_l, float desachs,
				 float in_del, float ex_del, Engine* parent);

		void process(float dp);
		void setP(float pfac);
		void setV(float newV);
		void setT(float newT);
		float setdP(float dp);

		bool ignition;

	private:
		float hub,bohrung,verdichtung,hubraum;
		float pleuel_l,desachs;
		int burntime;
public:		float V,P;
		float gasmenge,T,kolbflaeche;
		float x;	// kolbenposition

};


