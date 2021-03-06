#include "ExhaustSettings.h"

#define SUMLENGTH 500

ExhaustSettings::ExhaustSettings(Exhaust* p) : Settings(){

	xpos = 300;
	ypos = 20;

	this->parent = p;
	addParam("Sto�stelle 1",27,10,0,SUMLENGTH); 
	addParam("Sto�stelle 2",50,10,0,SUMLENGTH); 
	addParam("Sto�stelle 3",83,10,0,SUMLENGTH); 
	addParam("Sto�stelle 4",107,10,0,SUMLENGTH); 
	addParam("Sto�stelle 1 k1",0,0.05,-1,1); 
	addParam("Sto�stelle 2 k1",0,0.05,-1,1); 
	addParam("Sto�stelle 3 k1",0,0.05,-1,1); 
	addParam("Sto�stelle 4 k1",0,0.05,-1,1); 
	addParam("Tube Length",SUMLENGTH,10,5,SUMLENGTH); 
	addParam("Tube Gain",1,0.1,0,1); 
	addParam("Tube Cutoff",0.5,0.05,0,0.95); 
	addParam("Tube Order",1,1,1,20);
	addParam("Endref Gain",0.0,0.1,-0.95,0); 
	addParam("Endref Cutoff",0.05,0.01,0.01,1); 
	addParam("Endref Order",1,1,1,20);
	addParam("Tube Noise" ,0,0.1,0,2); 
	addParam("Exhaust Gain",0.5,0.1,0,10);

}

void ExhaustSettings::callbackSet(int p) {
	changed = true;
}
