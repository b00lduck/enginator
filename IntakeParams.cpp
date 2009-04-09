#include "IntakeParams.h"

#define SUMLENGTH 500

IntakeParams::IntakeParams(Intake* p) : Params(){
	this->parent = p;
	addParam("Stoﬂstelle 1",27,10,0,SUMLENGTH); 
	addParam("Stoﬂstelle 2",50,10,0,SUMLENGTH); 
	addParam("Stoﬂstelle 3",83,10,0,SUMLENGTH); 
	addParam("Stoﬂstelle 4",107,10,0,SUMLENGTH); 
	addParam("Stoﬂstelle 1 k1",0,0.05,-1,1); 
	addParam("Stoﬂstelle 2 k1",0,0.05,-1,1); 
	addParam("Stoﬂstelle 3 k1",0,0.05,-1,1); 
	addParam("Stoﬂstelle 4 k1",0,0.05,-1,1); 
	addParam("Tube Length",SUMLENGTH,10,5,SUMLENGTH); 
	addParam("Tube Gain",1,0.1,0,0.95); 
	addParam("Tube Cutoff",0.5,0.05,0,0.95); 
	addParam("Tube Order",1,1,1,20);
	addParam("Endref Gain",0.0,0.1,-0.95,0); 
	addParam("Endref Cutoff",0.05,0.01,0.01,1); 
	addParam("Endref Order",1,1,1,20);
	addParam("Intake Gain",5,0.5,0,10);			
}

void IntakeParams::callbackSet(int p) {
	changed = true;
}