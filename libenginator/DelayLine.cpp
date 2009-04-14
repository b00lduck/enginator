#include "DelayLine.h"

DelayLine::DelayLine(DWORD len) {
	length = len;
	delay = new float[len];
	clear();
}

DelayLine::~DelayLine() {
	SAFE_DELETE(delay);
}

void DelayLine::clear() {
	ZeroMemory(delay,sizeof(float)*length);
	readpos = 1;
	writepos = 0;
}


void DelayLine::advance() {
	//readpos = (++readpos % length);
	//writepos = (++writepos % length);
	readpos++;  while (readpos >= length) readpos -= length;
	writepos++; while (writepos >= length) writepos -= length;
}

float DelayLine::read() {
	return delay[readpos];
}


void DelayLine::writ(float in) {
	delay[writepos] = in;
}


void DelayLine::setLen(int len) {
	length = len;
}
