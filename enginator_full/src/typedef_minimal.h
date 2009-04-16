#pragma once

#define SAMPLERATE 44100

#define RENDERSLEEP 50					  // maximum Render sleep
#define GRANULARITY  120				  // render granularity (samples), must be vielfach von BLOCKSIZE
#define MAINBUFLEN   (GRANULARITY*40)	  // main buffer (samples)                  
#define MAINBUFBYTES (MAINBUFLEN * sizeof(DWORD))

#define RANGE(val,min,max) { if(val<min) val=min; else if (val>max) val=max;}
#define Clip(x) RANGE(x,-0.99f,0.99f);

#define PI 3.14159265f
#define RAD(x) ((PI/180.0f)*x)
#define DEG(x) (x*180.0f/PI)

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)		{ if(p) { delete(p); (p)=NULL; } }

static inline int Dither(float* in) {
  Clip(*in); 
  return (int)(32767 * (*in));
}

static inline void DitherStereo(DWORD* pDest, float* pSrcL, float* pSrcR, DWORD length_samples) {
  while(length_samples--)
	*pDest++ = (Dither(pSrcL++) << 16) + (Dither(pSrcR++)); 
}
