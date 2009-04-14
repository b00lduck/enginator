#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <math.h>
#include <process.h>
#include <dsound.h>


class Synth;

class CVSS {

	public:
		CVSS();
		~CVSS();

		HRESULT	Init( HWND hWnd );
		void Play();
		void Stop();
		void RenderTrigger();

		void setThrottle(float throttle);
		void setRPM(float rpm);
		void setIgnition(bool ignition);

		Synth*	p_Synth;

/*
		DWORD RenderThread();

		BOOL WriteToBuffer(LPDIRECTSOUNDBUFFER8 lpDsb, DWORD dwOffset, LPBYTE lpbSoundData, DWORD dwSoundBytes);

		HANDLE	m_syncEvent;
		HANDLE	m_hRenderThread; 

		long	m_samples_rendered;

		LPDIRECTSOUNDBUFFER8 m_pDSB;

		DWORD	m_bufplaypos;
		DWORD	m_lastbufplaypos;
		DWORD	m_buffersize;
		BOOL	m_bStopSoundThread;
		BOOL	m_playing;


		void Render(float* pDataL, float* pDataR, DWORD length);

		CRITICAL_SECTION CSRenderThread;
*/

};

