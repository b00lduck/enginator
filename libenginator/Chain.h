#pragma once
#include "vss_stdinc.h"
#include "HPFilt.h"
#include "ChainElement.h"

#define OFFSET_X 5
#define OFFSET_Y 50
#define ELEM_WIDTH 100
#define ELEM_HEIGHT 90
#define ELEM_GAP_X 2
#define ELEM_GAP_Y 5

#define NUMPARAMS 6

#define TEXTPADDING 2

#define TEXTHEIGHT ((ELEM_HEIGHT-TEXTPADDING*2)/NUMPARAMS)

class Chain {

public:
	Chain();
	~Chain();

	HPFilt *dc;

	void addElement(ChainElement *element);
	void setIDs();

	float process(float in);

	int numelements;
	
	ChainElement *elems[50];

};