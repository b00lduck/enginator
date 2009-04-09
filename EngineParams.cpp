#include "EngineParams.h"
#include "Engine.h"

EngineParams::EngineParams(Engine* p) : Params(){
	this->parent = p;
	addParam("Auslass Schärfe",	    5,     1,    0,    10);
	addParam("Auslass Q",		 0.26,  0.01,    0,     1); 
	addParam("Einlass Schärfe",	    5,     1,    0,    10);
	addParam("Einlass Q",		  0.1,  0.01,    0,     1);
	addParam("Motortyp",		    1,     1,    0,    3); 
	addParam("Noisefac",          0.5,   0.1,    0,     1);
}

void EngineParams::callbackSet(int p) {
	if (p == PARAM_ENG_TYPE) {
		parent->setEngineType(params[PARAM_ENG_TYPE]);
	}
	changed = true;
}
