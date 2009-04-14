#include "EnginePart.h"
#include "Engine.h"

EnginePart::EnginePart(Engine* parent) {
	this->parent = parent;
	this->phase = this->offset = offset;	// offset gegnüber KW
}

EnginePart::~EnginePart() {}

void EnginePart::move(float dp) {
	this->phase += dp;
	process(dp);
	if (phase >= FOUR_PI) phase -= FOUR_PI;
}

void EnginePart::setOffset(float of) {
	offset = of;
	phase = parent->phase + of;
}