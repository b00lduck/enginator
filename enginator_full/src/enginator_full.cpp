#include "enginator_full.h"

HINSTANCE			hInst;
ATOM				MyRegisterClass( HINSTANCE hInstance );
BOOL				InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );

CVSS* myVSS;
char text[500];
HFONT smFont = NULL;
bool clicked = true;

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

   smFont = CreateFont(10,0,0,0,0,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE|DEFAULT_PITCH,"Arial");

   hInst = hInstance;

   HWND hWnd = CreateWindow("VSS", "VSS", WS_OVERLAPPEDWINDOW, 100, 100, 1000, 600, NULL, NULL, hInstance, NULL);

   if( !hWnd ) return FALSE;

   ShowWindow( hWnd, nCmdShow );

   myVSS = new CVSS();

   SetTimer( hWnd, 1, 10, NULL );

   myVSS->Init( hWnd );  
   myVSS->Play();   	
 
   return TRUE;
}



void PaintText(HDC hdc) {

	RECT rt;

	rt.left = 20;
	rt.right = 600;
	rt.bottom = 420;
	rt.top = 400;
	
	if (myVSS) {
		sprintf_s(text,150,"rpm: %.0f                                ",rpm);
		DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
		sprintf_s(text,150,"inQ: %.2f                                ",myVSS->p_Synth->getProbe(0));
		DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
		sprintf_s(text,150,"outQ: %.2f                                ",myVSS->p_Synth->getProbe(1));
		DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
		sprintf_s(text,150,"phase: %.2f                                ",DEG(myVSS->p_Synth->getProbe(2)));
		DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
		sprintf_s(text,150,"x: %.2f                                ",myVSS->p_Synth->getProbe(3));
		DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
	}		
	
}


void PaintCyl(HDC hdc) {

	int x = 150;
	int y = 400;

	#define CYLWIDTH 50
	#define CYLHEIGHT 120
	#define CYLYOFFSET 20

	#define INVENTWIDTH 10
	#define INVENTHEIGHT 20
	#define INVENTYOFFSET 0
	#define INVENTXOFFSET 5

	#define OUTVENTWIDTH 10
	#define OUTVENTHEIGHT 20
	#define OUTVENTYOFFSET 0
	#define OUTVENTXOFFSET 35

	#define PISTHEIGHT 20
	#define PISTSPACE 2

	// Draw cylinder
	Rectangle(hdc,x,y+CYLYOFFSET,x+CYLWIDTH,y+CYLHEIGHT+CYLYOFFSET);

	// Draw piston
	int pisty = y + myVSS->p_Synth->getProbe(3) * 5;
	Rectangle(hdc,x+PISTSPACE,pisty+CYLYOFFSET,x+CYLWIDTH-PISTSPACE,pisty+PISTHEIGHT+CYLYOFFSET);

	// Draw InVent
	int inventy = y + myVSS->p_Synth->getProbe(0) * 10;
	Rectangle(hdc,x+INVENTXOFFSET,inventy+INVENTYOFFSET,
		          x+INVENTWIDTH+INVENTXOFFSET,inventy+INVENTHEIGHT+INVENTYOFFSET);

	// Draw InVentCurve
	
	int cx = myVSS->p_Synth->getProbe(2) * 30;
	int cy = myVSS->p_Synth->getProbe(0) * 50;
	SetPixel(hdc,x+cx+200,y+cy+50,0);

	// Draw OutVent
	int outventy = y + myVSS->p_Synth->getProbe(1) * 10;
	Rectangle(hdc,x+OUTVENTXOFFSET,outventy+OUTVENTYOFFSET,
		          x+OUTVENTWIDTH+OUTVENTXOFFSET,outventy+OUTVENTHEIGHT+OUTVENTYOFFSET);

	// Draw OutVentCurve
	
	cx = myVSS->p_Synth->getProbe(2) * 30;
	cy = myVSS->p_Synth->getProbe(1) * 50;
	SetPixel(hdc,x+cx+200,y+cy+100,0);



}



int limiter = 0;
float idle_throttle = 0;

void calcRPM() {

	float friction = 7.0f;
	float torque = 30.0f;
	float mass = 0.1f;
	float maxTorque = 5200.0f;

	if (limiter > 0) {
		torque = 0;
		ignition = false;
		limiter--;
	} else {
		if (rpm > 6500) {
			limiter = 5;
		} else {
			ignition = true;
		}
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
		idle_throttle += 0.1f;
	} else {
		if (idle_throttle > 0.1f) idle_throttle -= 0.1f;
	}

	//rpm = 20;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	int x = 0;
	int y = 0;

	switch( message ) {

  	  case WM_TIMER:
			InvalidateRect(hWnd,NULL,FALSE);
			UpdateWindow(hWnd);

			if (myVSS) {
				calcRPM();
				myVSS->setThrottle(throttle);
				myVSS->setRPM(rpm);
				myVSS->setIgnition(ignition);
				myVSS->RenderTrigger();		
			}
			break;	

	  case WM_KEYDOWN:
		  switch(wParam) {
			case VK_F1: throttle = 0.1f; break;
			case VK_F2: throttle = 0.22f; break;
			case VK_F3: throttle = 0.3f; break;
			case VK_F4: throttle = 0.4f; break;
			case VK_F5: throttle = 0.5f; break;
			case VK_F6: throttle = 0.6f; break;
			case VK_F7: throttle = 0.7f; break;
			case VK_F8: throttle = 0.8f; break;
			case VK_F9: throttle = 0.9f; break;
			case VK_SPACE: throttle = 1; break;
		  }

		  break;

	  case WM_KEYUP:
		  throttle = 0;
		  break;

	  case WM_LBUTTONUP:	
			myVSS->mouseUnclick();				    
			clicked=true;
		    break;

	  case WM_LBUTTONDOWN:
			x = (lParam & 0xffff);
			y = (lParam & 0xffff0000) >> 16;
			myVSS->mouseClick(x,y);
			clicked=true;
			break;

	  case WM_MOUSEMOVE:
			x = (lParam & 0xffff);
			y = (lParam & 0xffff0000) >> 16;
			myVSS->mouseMove(x,y);			
			clicked=true;
			break;

	  case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint (hWnd, &ps);

			PaintText(hdc);		
			PaintCyl(hdc);
			SelectObject(hdc, smFont); 

			if (myVSS) {
				if (clicked) {
					myVSS->drawParams(hdc);
					clicked=false;
				}
			}

			EndPaint( hWnd, &ps );
			break;

		case WM_DESTROY:
			SAFE_DELETE(myVSS);
			PostQuitMessage( 0 );
			break;

		default:

			return DefWindowProc( hWnd, message, wParam, lParam );
   }
   return 0;
}