#pragma once
#include "vss_stdinc.h"

class Engine;

class EnginePart {

	public:
		EnginePart(Engine* parent);
		~EnginePart();

		void move(float dp);
		virtual void process(float dp)=0;
		void setOffset(float of);

		Engine* parent;
		float offset;
		float phase;

};