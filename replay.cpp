#include "vss_stdinc.h"
#include "CVSS.h"
#include <process.h>
#include <dsound.h>

HINSTANCE			hInst;
ATOM				MyRegisterClass( HINSTANCE hInstance );
BOOL				InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );

CVSS* myVSS;
char text[500];
HFONT smFont = NULL;
bool clicked = true;

float throttle = 0;
float rpm = 750;
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
		sprintf(text,"rpm: %.0f                   ",rpm);
		DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
	//	sprintf(text,"gain: %.2f                   ",myVSS->p_Synth->myLimiter->gain);  
	//	DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
	//	sprintf(text,"env: %.2f                    ",myVSS->p_Synth->myLimiter->env);
	//	DrawText( hdc, text, 20, &rt, DT_LEFT ); rt.bottom += 20; rt.top += 20;
	}		
}


void calcRPM() {

	float friction = 100;
	float torque = 350;
	float mass = 1;
	float maxTorque = 5500;

	if (rpm > 7200) { 
		torque = 0;
		ignition = false;
	} else {
		ignition = true;	
	}

	float energy = (rpm*rpm) * mass;

	// friction
	energy -= friction * rpm;

	// power from engine
	if (rpm < maxTorque) {
		energy += torque * throttle * rpm;
	} else {
		energy += torque * throttle * (maxTorque*2 - rpm);	
	}

	if (energy < 0) energy = 0;

	rpm = sqrt(energy) / mass;

	if (rpm < 750) rpm = 750;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	int x = 0;
	int y = 0;

	switch( message ) {

  	  case WM_TIMER:
			InvalidateRect(hWnd,NULL,FALSE);
			UpdateWindow(hWnd);

			calcRPM();

			myVSS->setThrottle(throttle);
			myVSS->setRPM(rpm);
			myVSS->setIgnition(ignition);

			myVSS->RenderTrigger();		
			break;	

	  case WM_KEYDOWN:
		  if (wParam == VK_SPACE)               
			  throttle = 1;
		  break;

	  case WM_KEYUP:
		  if (wParam == VK_SPACE) 
			  throttle = 0.1;
		  break;

	  case WM_LBUTTONUP:
			myVSS->p_Synth->myEngine->params->unClick();			
			myVSS->p_Synth->myExhaust1->params->unClick();
			myVSS->p_Synth->myExhaust2->params->unClick();
			myVSS->p_Synth->myIntake->params->unClick();		    
			clicked=true;
		    break;

	  case WM_LBUTTONDOWN:
			x = (lParam & 0xffff);
			y = (lParam & 0xffff0000) >> 16;
			myVSS->p_Synth->myEngine->params->click(20,20,x,y,1);			
			myVSS->p_Synth->myExhaust1->params->click(300,20,x,y,1);
			myVSS->p_Synth->myExhaust2->params->click(300,20,x,y,1);
			myVSS->p_Synth->myIntake->params->click(580,20,x,y,1);
			clicked=true;
			break;

	  case WM_RBUTTONDOWN:
			x = (lParam & 0xffff);
			y = (lParam & 0xffff0000) >> 16;
			myVSS->p_Synth->myEngine->params->click(20,20,x,y,-1);
			myVSS->p_Synth->myExhaust1->params->click(300,20,x,y,-1);
			myVSS->p_Synth->myExhaust2->params->click(300,20,x,y,-1);
			myVSS->p_Synth->myIntake->params->click(580,20,x,y,-1);
			clicked=true;
			break;

	  case WM_MOUSEMOVE:
			x = (lParam & 0xffff);
			y = (lParam & 0xffff0000) >> 16;
			myVSS->p_Synth->myEngine->params->move(20,20,x,y);
			myVSS->p_Synth->myExhaust1->params->move(300,20,x,y);
			myVSS->p_Synth->myExhaust2->params->move(300,20,x,y);
			myVSS->p_Synth->myIntake->params->move(580,20,x,y);
			clicked=true;
			break;

	  case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint (hWnd, &ps);

			PaintText(hdc);		
			SelectObject(hdc, smFont); 

			if (myVSS) {
				if (clicked) {
					myVSS->p_Synth->myEngine->params->draw(hdc,20,20);
					myVSS->p_Synth->myExhaust1->params->draw(hdc,300,20);
					myVSS->p_Synth->myExhaust2->params->draw(hdc,300,20);
					myVSS->p_Synth->myIntake->params->draw(hdc,580,20);
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