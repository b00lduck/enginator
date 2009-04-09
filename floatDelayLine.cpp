#include "floatDelayLine.h"

floatDelayLine::floatDelayLine(DWORD len) {
	delay1 = new DelayLine(len);
	delay2 = new DelayLine(len);
}

floatDelayLine::~floatDelayLine() {
	delete(delay1);
	delete(delay2);
}

void floatDelayLine::advance() {
	delay1->advance();
	delay2->advance();
}

void floatDelayLine::setLen(int len) {
	delay1->setLen(len);
	delay2->setLen(len);
}