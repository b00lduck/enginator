#include "vss_stdinc.h"
#include "dsound.h"
#include "Synth.h"

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

		HANDLE	m_syncEvent;
		HANDLE	m_hRenderThread; 

	private:
		HRESULT	CreateBasicBuffer(LPDIRECTSOUND8 lpDirectSound, LPDIRECTSOUNDBUFFER8* ppDsb8);

		HWND	m_hWnd;
		HANDLE	m_hBuffer;

		LPDIRECTSOUND8   m_pDS;

		DWORD	m_eventcount;

		bool renderThreadIsDone;

	public:

		long	m_samples_rendered;

		LPDIRECTSOUNDBUFFER8 m_pDSB;

		DWORD	m_bufplaypos;
		DWORD	m_lastbufplaypos;
		DWORD	m_buffersize;
		BOOL	m_bStopSoundThread;
		BOOL	m_playing;

		Synth*	p_Synth;
		void Render(float* pDataL, float* pDataR, DWORD length);

		CRITICAL_SECTION CSRenderThread;

};



