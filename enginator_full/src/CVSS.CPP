#define INITGUID
#include "cvss.h"


CVSS* MYVSS = NULL;

CVSS::CVSS() {
	MYVSS = this;
	m_hWnd = NULL;
	m_pDS = NULL;
	m_pDSB = NULL;
	m_buffersize = 0;
	m_lastbufplaypos = 0;
	m_bufplaypos = 0;
	m_bStopSoundThread = FALSE;
	m_playing = FALSE;
	m_samples_rendered = -MAINBUFLEN;
	m_eventcount = 0;
	m_syncEvent = NULL;
	p_Synth = new Synth();
}

void CVSS::setThrottle(float throttle) {
	p_Synth->setThrottle(throttle);
}

void CVSS::setRPM(float rpm) {
	p_Synth->setRPM(rpm);
}

void CVSS::setIgnition(bool ignition) {
	p_Synth->setIgnition(ignition);
}

DWORD CVSS::RenderThread() {

	renderThreadIsDone = false;

	float* pDataL = NULL;
	float* pDataR = NULL;
	LPBYTE	pFinalBuf = NULL;

	DWORD size;

	// Get Buffers
	pDataL = (float*) malloc(MAINBUFLEN * sizeof(float));
	pDataR = (float*) malloc(MAINBUFLEN * sizeof(float));
	pFinalBuf = (LPBYTE) malloc(MAINBUFBYTES);

	// !!! HIER ALLE *LÄNGEN* IN BYTES !!!
	while ((m_bStopSoundThread == FALSE) && (p_Synth)) {
		EnterCriticalSection(&CSRenderThread);
		m_pDSB->GetCurrentPosition(&m_bufplaypos,NULL);  // Bufferposition in bytes holen
		if (m_bufplaypos >= m_lastbufplaypos) {
			size = m_bufplaypos - m_lastbufplaypos;
		} else {
			size = MAINBUFBYTES - m_lastbufplaypos;
		}
		size -= size % (GRANULARITY << 2);
		if (size > 0) {
			p_Synth->synthRender(pDataL,pDataR,size >> 2);
			DitherStereo((DWORD*)pFinalBuf,pDataL,pDataR,size >> 2);
			WriteToBuffer(m_pDSB,m_lastbufplaypos,pFinalBuf,size);
			m_samples_rendered += size >> 2;
			m_lastbufplaypos = (m_lastbufplaypos + size) % MAINBUFBYTES;
		}
		LeaveCriticalSection(&CSRenderThread);
		WaitForSingleObject(m_syncEvent,RENDERSLEEP);
	}

	renderThreadIsDone = true;
	return 0;
}

HRESULT CVSS::Init( HWND hWnd ) {
	m_hWnd = hWnd;

	// Set up direct sound
	DirectSoundCreate8(NULL,&m_pDS,NULL);	
	m_pDS->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);	
	CreateBasicBuffer(m_pDS,&m_pDSB);

	SECURITY_ATTRIBUTES eventAttr;

	eventAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	eventAttr.lpSecurityDescriptor = NULL;
	eventAttr.bInheritHandle = TRUE;

	m_syncEvent = CreateEvent(&eventAttr,FALSE,FALSE,NULL);

	InitializeCriticalSection(&CSRenderThread);

	return S_OK; 
}

DWORD WINAPI _renderThread(void* dummy) {
	UNREFERENCED_PARAMETER(dummy);
	return MYVSS->RenderThread();
}

void CVSS::Play() {
    m_pDSB->Play(0,0,DSBPLAY_LOOPING);
	DWORD dwThreadId; 
    char szMsg[80];
    m_hRenderThread = CreateThread( 
        NULL,                        // default security attributes 
        0,                           // use default stack size  
        _renderThread,                // thread function 
        NULL,		                 // argument to thread function 
        0,                           // use default creation flags 
        &dwThreadId);                // returns the thread identifier 
 
   // Check the return value for success. 
    if (m_hRenderThread == NULL) {
      wsprintf( szMsg, "CreateThread failed." ); 
      MessageBox( NULL, szMsg, "main", MB_OK );
   }
	SetThreadPriority(m_hRenderThread, THREAD_PRIORITY_HIGHEST);
}

void CVSS::Stop() {
	m_bStopSoundThread = TRUE;
	m_pDSB->Stop();
}

void CVSS::RenderTrigger() {
	SetEvent(m_syncEvent);
}

HRESULT CVSS::CreateBasicBuffer(LPDIRECTSOUND8 lpDirectSound, LPDIRECTSOUNDBUFFER8* ppDsb8) { 

	WAVEFORMATEX wfx; 
	DSBUFFERDESC dsbdesc; 
	LPDIRECTSOUNDBUFFER pDsb = NULL;
	HRESULT hr; 

	// Set up WAV format structure. 
	memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
	wfx.wFormatTag = WAVE_FORMAT_PCM; 
	wfx.nChannels = 2; 
	wfx.nSamplesPerSec = SAMPLERATE;
	wfx.nBlockAlign = 4; 
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign; 
	wfx.wBitsPerSample = 16; 

	// Set up DSBUFFERDESC structure. 
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS; 
	dsbdesc.dwBufferBytes = MAINBUFLEN * wfx.nBlockAlign; 
	dsbdesc.lpwfxFormat = &wfx; 

	m_buffersize = dsbdesc.dwBufferBytes;

	// Create buffer. 
	hr = lpDirectSound->CreateSoundBuffer(&dsbdesc, &pDsb, NULL); 
	if (SUCCEEDED(hr)) { 
	 hr = pDsb->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*) ppDsb8);
	 pDsb->Release();
	} 
	return hr;
} 

BOOL CVSS::WriteToBuffer( 
    LPDIRECTSOUNDBUFFER8 lpDsb,  // The buffer.
    DWORD dwOffset,              // Our own write cursor.
    LPBYTE lpbSoundData,         // Start of our data.
    DWORD dwSoundBytes)          // Size of block to copy.
{ 
	LPVOID  lpvPtr1; 
	DWORD dwBytes1; 
	LPVOID  lpvPtr2; 
	DWORD dwBytes2; 
	HRESULT hr; 

	hr = lpDsb->Lock(dwOffset, dwSoundBytes, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0); 
	if (SUCCEEDED(hr)) { 
		CopyMemory(lpvPtr1, lpbSoundData, dwBytes1); 
		if (NULL != lpvPtr2) { 
			CopyMemory(lpvPtr2, lpbSoundData+dwBytes1, dwBytes2); 
		} 
		hr = lpDsb->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2); 
		if (SUCCEEDED(hr)) { 
			return TRUE; 
		} 
	} 

	return FALSE; 
} 

void CVSS::mouseUnclick() {
	p_Synth->unclick();
}

void CVSS::mouseMove(int x, int y) {
	p_Synth->move(x,y);
}

void CVSS::mouseClick(int x, int y) {
	p_Synth->click(x,y);
}

void CVSS::drawParams(HDC hdc) {
	p_Synth->draw(hdc);
}

CVSS::~CVSS() {

	while (!renderThreadIsDone) {
		m_bStopSoundThread = TRUE;
	}
	
	DeleteCriticalSection(&CSRenderThread);

	SAFE_RELEASE(m_pDSB);
	SAFE_RELEASE(m_pDS); 

	SAFE_DELETE(p_Synth);
}


