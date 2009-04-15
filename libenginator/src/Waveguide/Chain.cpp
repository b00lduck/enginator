#include "Chain.h"

Chain::Chain() {
	numelements = 0;
	dc = new HPFilt(0.005,1,1);
}

void Chain::addElement(ChainElement* element) {
	elems[numelements] = element;
	numelements++;
}

Chain::~Chain() {
	delete(dc);
}

void Chain::setIDs() {
	for(int i=0;i<numelements;i++) {
		elems[i]->setIDs(i,numelements,this);
		elems[i]->setup();
	}
}

float Chain::process(float in) {
	in = dc->tick(in);
	for (int i=0;i<(numelements-1);i++) {
		elems[i]->process(in);
	}
	float out = elems[numelements-1]->process(0);
	return out;
}