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

		HANDLE	m_syncEvent;
		HANDLE	m_hRenderThread; 

		long	m_samples_rendered;

		LPDIRECTSOUNDBUFFER8 m_pDSB;

		DWORD	m_bufplaypos;
		DWORD	m_lastbufplaypos;
		DWORD	m_buffersize;
		BOOL	m_bStopSoundThread;
		BOOL	m_playing;

		Synth*	p_Synth;


};



