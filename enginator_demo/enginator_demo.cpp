#include "enginator_demo.h"

HINSTANCE			hInst;
ATOM				MyRegisterClass( HINSTANCE hInstance );
BOOL				InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );

CVSS* myVSS;

float throttle = 0;
float rpm = 2000;
bool ignition = true;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	MSG msg;
	MyRegisterClass(hInstance);
	if( !InitInstance( hInstance, nCmdShow ) ) return FALSE;
	while( GetMessage(&msg, NULL, 0, 0) ) DispatchMessage( &msg );
	return msg.wParam;
}

ATOM MyRegisterClass( HINSTANCE hInstance ) {

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "VSS";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance( HINSTANCE hInstance, int nCmdShow ) {

   hInst = hInstance;

   HWND hWnd = CreateWindow("VSS", "VSS", WS_OVERLAPPEDWINDOW, 100, 100, 1000, 600, NULL, NULL, hInstance, NULL);

   if( !hWnd ) return FALSE;

   ShowWindow( hWnd, nCmdShow );

   myVSS = new CVSS();

   SetTimer( hWnd, 1, 20, NULL );

   myVSS->Init( hWnd );  
   myVSS->Play();   	
 
   return TRUE;
}

int limiter = 0;
float idle_throttle = 0;

void calcRPM() {

	float friction = 20  ;
	float torque = 50 ;
	float mass = 0.5;
	float maxTorque = 4500;

	if (rpm > 7200) {
		limiter = 4  ;
	}
	if (limiter >0) {
		torque = 0;
		ignition = false;
		limiter--;
	} else {
		ignition = true;
	}

	float energy = (rpm*rpm) * mass;

	// friction
	energy -= friction * rpm;

	// power from engine
	if (rpm < maxTorque) {
		energy += torque * (throttle + idle_throttle) * rpm;
	} else {
		energy += torque * (throttle + idle_throttle) * (maxTorque*2 - rpm);	
	}

	if (energy < 0) energy = 0;

	rpm = sqrt(energy / mass);

	if (rpm < 750) { 
		idle_throttle += 0.01f;
	} else {
		if (idle_throttle > 0.01f) idle_throttle -= 0.01f;
	}
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch( message ) {

  		case WM_TIMER:

//			InvalidateRect(hWnd,NULL,FALSE);
//			UpdateWindow(hWnd);
			calcRPM();
			myVSS->setThrottle(throttle);
			myVSS->setRPM(rpm);
			myVSS->setIgnition(ignition);
			myVSS->RenderTrigger();		
			break;	

		case WM_KEYDOWN:
			if (wParam == VK_SPACE) throttle = 1;
			break;

		case WM_KEYUP:
			if (wParam == VK_SPACE) throttle = 0;
			break;

		case WM_DESTROY:
			if (myVSS) {
				delete(myVSS);
				myVSS = 0;
			}
			PostQuitMessage( 0 );
			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
   }
   return 0;
}