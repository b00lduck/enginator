#pragma once
//#include "vss_stdinc.h"
#include "Params.h"

enum {  PARAM_ENG_OUT_SH=0,
		PARAM_ENG_OUT_Q,
		PARAM_ENG_IN_SH,
		PARAM_ENG_IN_Q,	
		PARAM_ENG_TYPE,	
		PARAM_ENG_NOISE,
		PARAM_ENG_RPM,
		PARAM_ENG_THROTTLE};

class Engine;

class EngineParams : public Params{
	public:

	EngineParams(Engine* parent);
	void callbackSet(int p);
	Engine* parent;

};	