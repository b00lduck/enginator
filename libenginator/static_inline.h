/***************************************************/
/* static_inline.h								   */
/*												   */
/* Virtual Sound System							   */
/* (c) 2003 Daniel Zerlett						   */
/*												   */
/***************************************************/
#pragma once


/*****************************************************/
static inline int Dither(float* in) {
/*****************************************************/
  Clip(*in); 
  return (int)(32767 * (*in));
}

/*****************************************************/
static inline float MIN(float a, float b) {
/*****************************************************/
	if (a > b) return b;
	return a;
}

/*****************************************************/
static inline float MAX(float a, float b) {
/*****************************************************/
	if (a < b) return b;
	return a;
}

/*********************************************************/
static inline void DitherStereo(DWORD* pDest, float* pSrcL, float* pSrcR, DWORD length) {
/*********************************************************/
  while(length--)
	*pDest++ = (Dither(pSrcL++) << 16) + (Dither(pSrcR++)); 
}

