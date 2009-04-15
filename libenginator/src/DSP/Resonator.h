#pragma once
#include "CFilter.h"

class Resonator {

public:
	Resonator();
	~Resonator();

	void addRes(float freq, float res, float vol);
	float tick(float in);

	CFilter* resos[255];

	int rescount;

};
