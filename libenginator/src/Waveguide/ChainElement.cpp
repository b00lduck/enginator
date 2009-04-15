#include "ChainElement.h"
#include "Chain.h"

ChainElement::ChainElement() {
	a = b = c = d = 0;
	dc = new HPFilt(0.05,1,1);
}

ChainElement::~ChainElement() {
	delete(dc);
}

void ChainElement::setIDs(int id, int numelements, Chain* p) {
	parent = p;
	next_element = id+1;
	prev_element = id-1;
	if (next_element == numelements) next_element = -1;
}

float ChainElement::process(float in) {

	if (this == NULL) return 0;

	lastin = in;

	if (prev_element == -1) {
		if (next_element == -1) {
			// First and last element
			transform();
		} else {
			// First element
			d = parent->elems[next_element]->c;	
			transform();
			parent->elems[next_element]->a = b;
		}
		

	} else if (next_element == -1) {
		// Last element
		a = parent->elems[prev_element]->b;
		//d = 0;
				
		transform();

		parent->elems[prev_element]->d = c;

		return b;

	} else {
		// Intermediate element
		a = parent->elems[prev_element]->b;
		d = parent->elems[next_element]->c;
				
		transform();

		parent->elems[next_element]->a = b;
		parent->elems[prev_element]->d = c;
	}

	return 0;
}


