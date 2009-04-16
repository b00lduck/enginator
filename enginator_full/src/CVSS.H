#pragma once
#include <dsound.h>
#include <mmsystem.h>
#include "Synth_minimal.h"
#include "typedef_minimal.h"

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

		DWORD RenderThread();

		BOOL WriteToBuffer(LPDIRECTSOUNDBUFFER8 lpDsb, DWORD dwOffset, LPBYTE lpbSoundData, DWORD dwSoundBytes);


		void mouseUnclick();
		void mouseMove(int x, int y);
		void mouseClick(int x, int y);
		void drawParams(HDC hdc);

		Synth*	p_Synth;

	private:

		HANDLE	m_syncEvent;
		HANDLE	m_hRenderThread; 

		HRESULT	CreateBasicBuffer(LPDIRECTSOUND8 lpDirectSound, LPDIRECTSOUNDBUFFER8* ppDsb8);

		HWND	m_hWnd;
		HANDLE	m_hBuffer;

		LPDIRECTSOUND8   m_pDS;

		DWORD	m_eventcount;

		bool renderThreadIsDone;

		long	m_samples_rendered;

		LPDIRECTSOUNDBUFFER8 m_pDSB;

		DWORD	m_bufplaypos;
		DWORD	m_lastbufplaypos;
		DWORD	m_buffersize;
		BOOL	m_bStopSoundThread;
		BOOL	m_playing;

		void Render(float* pDataL, float* pDataR, DWORD length);

		CRITICAL_SECTION CSRenderThread;

};



