#include "perfWaveGuide.h"

perfWaveGuide::perfWaveGuide(DWORD len) {
	length = len;
	delay1 = new float[len];
	delay2 = new float[len];
	clear();
	maxoff = length - 1;
	endFB_filt = NULL;
	setTubeFilt(1,1,1); // Allpass, no delay
	last_fb = 0;
	ss_count = 0;	
}

perfWaveGuide::~perfWaveGuide() {
	SAFE_DELETE(delay1);
	SAFE_DELETE(delay2);
	SAFE_DELETE(endFB_filt);
	for(int i=0;i<ss_count;i++) {
		SAFE_DELETE(ss_filt1[i]);
		SAFE_DELETE(ss_filt2[i]);
		SAFE_DELETE(noise1[i]);
		SAFE_DELETE(noise2[i]);

	}
}

void perfWaveGuide::clear() {
	ZeroMemory(delay1,sizeof(float)*length);
	ZeroMemory(delay2,sizeof(float)*length);
	startpos = 0;
}


float perfWaveGuide::process(float in) {
	// advance
	startpos++; while (startpos >= length) startpos -= length;
	
	// FBUp
	delay1[getpos1(0)] = in + delay2[getpos2(0)];	
	
	// Stosstelle
	for(int i=0;i<ss_count;i++) {
		if (ss_pos[i] > 0) {
			#ifdef NORMALIZED_SCATTERING
			// (normalized)
			float a = delay1[getpos1(ss_pos[i])];
			float d = delay2[getpos2(ss_pos[i])];		
			float p = ss_k1[i]*(a-d);
			float b = a+p;
			float c = p+d;
			
			delay1[getpos1(ss_pos[i])] = b;
			float pa = abs(b);
			if (pa > 0.1) {
				delay1[getpos1(ss_pos[i])] += (noise1[i]->tick()) * (pa - 0.1) / 5.0f;
			}
				
			delay2[getpos2(ss_pos[i])] = c;
			float qa = abs(c);
			if (qa > 0.1) {
				delay2[getpos2(ss_pos[i])] += (noise2[i]->tick()) * (qa - 0.1) / 5.0f;		
			}

			delay1[getpos1(ss_pos[i])] = ss_filt1[i]->tick(delay1[getpos1(ss_pos[i])]);
			delay2[getpos2(ss_pos[i])] = ss_filt2[i]->tick(delay2[getpos2(ss_pos[i])]);


			#else
			// (not normalized)
			float a = ss_filt1[i]->tick(delay1[getpos1(ss_pos[i])]);
			float d = delay2[getpos2(ss_pos[i])];		
			float p = ss_k1[i]*(a-d);
			float b = a+p;
			float c = ss_filt2[i]->tick(p+d);
			delay1[getpos1(ss_pos[i])] = (b + noise1[i]->tick()) ;
			delay2[getpos2(ss_pos[i])] = (c + noise2[i]->tick()) ;		
			#endif		
		}
	}

	// FBDown
	float tmp = delay1[getpos1(maxoff)];
	delay2[getpos2(maxoff)] = endFB_filt->tick(tmp);
	
	return tmp;							// transmitted
}

inline DWORD perfWaveGuide::getpos1(DWORD offset) {
	long pos = startpos-offset;
	while (pos < 0) pos += length;
	return pos;
}

inline DWORD perfWaveGuide::getpos2(DWORD offset) {
	long pos = startpos+1+offset;
	while (pos >= length) pos -= length;
	return pos;
}

void perfWaveGuide::setEndFB(int o, float c, float g) {
	SAFE_DELETE(endFB_filt);
	endFB_filt = new IIR();
	endFB_filt->setLowpass(o,c,g);
}

void perfWaveGuide::setTubeFilt(int o, float c, float g) {
	tube_c = c;
	tube_o = o;
	tube_g = g;
}


void perfWaveGuide::addNormalizedJunction(DWORD pos, int o, float c, float g) {
	if (pos > 0) {
		ss_pos[ss_count] = pos;
		ss_k1[ss_count] = g;
		ss_filt1[ss_count] = new IIR();
		ss_filt2[ss_count] = new IIR();
		ss_filt1[ss_count]->setLowpass(tube_o,tube_c,tube_g);
		ss_filt2[ss_count]->setLowpass(tube_o,tube_c,tube_g);
		#ifdef NORMALIZED_SCATTERING
		ss_g[ss_count] = sqrt((1-g)/(1+g));
		ss_g_inv[ss_count] = 1.0f / ss_g[ss_count];
		#endif
		noise1[ss_count] = new Noise();
		noise2[ss_count] = new Noise();
		ss_count++;
	}
}