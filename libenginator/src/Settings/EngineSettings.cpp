#include "EngineSettings.h"
#include "Engine.h"

EngineSettings::EngineSettings(Engine* p) : Settings(){
	this->parent = p;

	xpos = 20;
	ypos = 20;

	addParam("Auslass Schärfe",	    5,     1,    1,    20);
	addParam("Auslass Q",		 0.26,  0.01,    0,    51); 
	addParam("Einlass Schärfe",	    5,     1,    1,    20);
	addParam("Einlass Q",		  0.1,  0.01,    0,    51);
	addParam("Motortyp",		    1,     1,    0,     3); 
	addParam("Noisefac",          0.5,   0.1,    0,     1);
}

void EngineSettings::callbackSet(int p) {
	if (p == PARAM_ENG_TYPE) {
		parent->setEngineType(getParameter(PARAM_ENG_TYPE));
	}
	if (p == PARAM_ENG_OUT_SH) {
		parent->setOutVentsSharpness(getParameter(PARAM_ENG_OUT_SH));
	}
	if (p == PARAM_ENG_IN_SH) {
		parent->setInVentsSharpness(getParameter(PARAM_ENG_IN_SH));
	}


	changed = true;
}
