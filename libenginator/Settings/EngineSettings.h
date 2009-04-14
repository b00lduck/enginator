#pragma once
//#include "vss_stdinc.h"
#include "Settings.h"

enum {  PARAM_ENG_OUT_SH=0,
		PARAM_ENG_OUT_Q,
		PARAM_ENG_IN_SH,
		PARAM_ENG_IN_Q,	
		PARAM_ENG_TYPE,	
		PARAM_ENG_NOISE};

class Engine;

class EngineSettings : public Settings{
	public:

	EngineSettings(Engine* parent);
	void callbackSet(int p);
	Engine* parent;

};	