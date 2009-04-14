#pragma once
#include "vss_stdinc.h"
#include "Zylinder.h"
#include "Ventil.h"
#include "EngineSettings.h"
#include "Noise.h"
#include "LPFilt.h"

#define MAXCYLS		 12
#define MAXVENTS	 (MAXCYLS*2)
#define INVENTOFFSET MAXCYLS

#define ZEROCHK(x) { if (x < 0) x = 0; }
#define NOCKCHK(x) { if (x < 0) x += 720; if (x > 719) x -= 720; }
#define CYLCHK(x)  { if (x< 1) x = 1; if (x > MAXCYLS) x=MAXCYLS; }

#define IS_VENG 256

#define ENGINETYPE_R3	  (3)
#define ENGINETYPE_R4     (4)
#define ENGINETYPE_R6     (6)
#define ENGINETYPE_V8     (8+IS_VENG)

#define ENGINETYPES 4  

class Engine {

	public:
	
		Engine();
		~Engine();

		float move();

		void setThrottle(float throttle);
		void setRPM(float rpm);
		void setIgnition(bool ignition);
		void process();

		void setEngineType(int engtype);
		void setCyls(int cyls);
		
		float exhaust[MAXCYLS];
		float intake[MAXCYLS];

		float phase;
		int cyls;

		EngineSettings *params;

		bool ignition;
		
		float getThrottle();

	private:

		float throttle;
	
	public:

		Zylinder *myCyls[MAXCYLS];
		Ventil *myOutVents[MAXVENTS];
		Ventil *myInVents[MAXVENTS];

		int is_v,type;

		float rpm;

		Noise* exhaust_noise;
		Noise* intake_noise;

		LPFilt* throttleFilter;

};