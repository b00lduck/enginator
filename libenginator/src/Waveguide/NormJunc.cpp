#include "vss_stdinc.h"
#include "NormJunc.h"

NormJunc::NormJunc(float k1) : ChainElement() {
	this->k1 = k1;
}

NormJunc::~NormJunc() {}

void NormJunc::setup() {}

void NormJunc::transform() {
	b = a * (1+k1) - d * k1;
	c = a * k1 + d * (1-k1);
}