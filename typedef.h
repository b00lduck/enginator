#pragma once

// Rendering/Replay stuff
#define SAMPLERATE 44100 

/*** Performance settings ***/
#define RENDERSLEEP 50					  // maximum Render sleep
#define GRANULARITY  120		  // render granularity (samples), must be vielfach von BLOCKSIZE
#define MAINBUFLEN   (GRANULARITY*40)	  // main buffer (samples)                  
#define MAINBUFBYTES (MAINBUFLEN * sizeof(DWORD))

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)		{ if(p) { delete(p); (p)=NULL; } }

// PI-Definition
#define PI_180			0.01745329f
#define PI				3.14159265f
#define PI_2			1.57079632f
#define PI_4			0.78539816f
#define TWO_PI		6.28318530f
#define FOUR_PI		12.5663706f
#define PI2				6.28318530f
#define PI4				12.5663706f

#define VOLUME 0,0.001,0,10

#define POW2(x)	(x)*(x)
#define Clip(x) RANGE(x,-0.99f,0.99f);

#define RANGE(val,min,max) { if(val<min) val=min; else if (val>max) val=max;}
#define FLIP_4PI(val) { while (val<PI4) val+=PI4; while (val>PI4) val-=PI4; }


// Winkel
#define RAD(x) (PI_180*x)
#define DEG(x) (x/PI_180)

// Parameter
#define _P(x) params->params[x]

#define SIGNAL float

#define VERY_SMALL_FLOAT (0.000001f)

