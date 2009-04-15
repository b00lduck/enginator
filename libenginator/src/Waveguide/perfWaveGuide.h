#pragma once
#include "vss_stdinc.h"
#include "IIR.h"
#include "Noise.h"

class perfWaveGuide {

	public:
		perfWaveGuide (DWORD len);
		~perfWaveGuide ();

		void setEndFB(int o,float c, float g);
		void setTubeFilt(int o,float c, float g);
		void addNormalizedJunction(DWORD pos, int o, float c, float g);
		
		float process(float in, float kstart);

		float last_fb;

		void setNoiseFactor(float noisefactor);

	private:
		void clear();

		inline DWORD getpos1(DWORD offset);
		inline DWORD getpos2(DWORD offset);

		float *delay1,*delay2;



		DWORD length,startpos,maxoff;

		IIR *endFB_filt;

		#define MAX_SCATTER 10

		// Stoﬂstelle
		float ss_g[MAX_SCATTER];
		float ss_g_inv[MAX_SCATTER];

		IIR *ss_filt1[MAX_SCATTER];
		IIR *ss_filt2[MAX_SCATTER];
		DWORD ss_pos[MAX_SCATTER];
		float ss_k1[MAX_SCATTER];
		DWORD ss_count;

		float tube_c;
		float tube_o;
		float tube_g;
		float tube_noisefactor;

		Noise* noise1[MAX_SCATTER];
		Noise* noise2[MAX_SCATTER];

};

