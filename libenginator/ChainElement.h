#pragma once
#include "vss_stdinc.h"
#include "HPFilt.h"

class Chain;

class ChainElement {

public:
	ChainElement();
	~ChainElement();
	
	void setIDs(int id, int numelements, Chain* par) ;

	float process(float in);
	virtual void transform()=0;
	virtual void setup()=0;

	float lastin;

	float a,b,c,d;

	DWORD next_element;
	DWORD prev_element;

	HPFilt *dc;

	Chain *parent;

};


