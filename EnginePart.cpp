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
	FLIP_4PI(phase);
}

void EnginePart::setOffset(float of) {
	offset = of;
	phase = parent->phase + of;
}