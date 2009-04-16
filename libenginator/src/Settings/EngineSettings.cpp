#include "EngineSettings.h"
#include "Engine.h"

EngineSettings::EngineSettings(Engine* p) : Settings(){
	this->parent = p;

	xpos = 20;
	ypos = 20;

	addParam("Auslass open",		390,      1,    0,    719);
	addParam("Auslass close",		719,      1,    0,    719);
	addParam("Auslass Schärfe",	    5,     1,    1,    20);
	addParam("Auslass Q",			0.26,  0.01,    0,    51); 
	addParam("Einlass open",		0,      1,    0,    719);
	addParam("Einlass close",		180,      1,    0,    719);
 	addParam("Einlass Schärfe",	    5,     1,    1,    20);
	addParam("Einlass Q",			0.1,  0.01,    0,    51);
	addParam("Motortyp",		    1,     1,    0,     3); 
	addParam("Noisefac",			0.5,   0.1,    0,     1);
}

void EngineSettings::callbackSet(int p) {
	switch(p) {
		case PARAM_ENG_TYPE:
			parent->setEngineType(getParameter(PARAM_ENG_TYPE));
			break;
		case PARAM_ENG_OUT_SH:

			parent->setOutVentsSharpness(getParameter(PARAM_ENG_OUT_SH));
			break;
		case PARAM_ENG_OUT_START:
		case PARAM_ENG_OUT_STOP:
			parent->setOutVentsTiming(getParameter(PARAM_ENG_OUT_START),getParameter(PARAM_ENG_OUT_STOP));
			break;
		case PARAM_ENG_IN_SH:
			parent->setInVentsSharpness(getParameter(PARAM_ENG_IN_SH));
			break;				
		case PARAM_ENG_IN_START:
		case PARAM_ENG_IN_STOP:
			parent->setInVentsTiming(getParameter(PARAM_ENG_IN_START),getParameter(PARAM_ENG_IN_STOP));
			break;
				
	}


	changed = true;
}
