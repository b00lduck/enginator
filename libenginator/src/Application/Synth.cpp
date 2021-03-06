#include "Synth.h"


static inline int Dither(float* in) {
  Clip(*in); 
  return (int)(32767 * (*in));
}


Synth::Synth() {

	myEngine = new Engine();
	myIntake = new Intake();
	myExhaust = new Exhaust();

	myHPL = new IIR();
	myHPR = new IIR();
	myHPL->setLowpass(1,0.1f,1);
	myHPR->setLowpass(1,0.1f,1);

	//Limiter: thresh, slope, tla, twnd, tatt, trel
	myLimiter = new Limiter(0.95f, 0.01f, 1.0f);

	pDataL = (float*) malloc(SAMPLERATE * sizeof(float));
	pDataR = (float*) malloc(SAMPLERATE * sizeof(float));

}

Synth::~Synth() {
	SAFE_DELETE(myExhaust);
	SAFE_DELETE(myIntake);
	SAFE_DELETE(myEngine);	
	SAFE_DELETE(myHPL);
	SAFE_DELETE(myHPR);
	SAFE_DELETE(myLimiter);
}

void Synth::synthRender(float* pDataL, float* pDataR, DWORD length_samples) {

	float left,right;

	while (length_samples > 0) {
		float sound1 = 0;		
		float sound2 = 0;
			
		myEngine->move();	
		myEngine->process();		
			
		int banks[8] = { 1, 1, 1, 1 , 1, 1, 0, 0 };
		
		float engineout = 0;
		float enginein = 0;
		
		for(int i=0;i<myEngine->cyls;i++) {	
			engineout += myEngine->exhaust[i] * (0.5f + i/6.0f);
			enginein += myEngine->intake[i] * (0.5f + i/6.0f);
		}

		myIntake->process(enginein);		
		myExhaust->process(engineout);

		left = right = 0;
		
		sound1 = myExhaust->lastOutL;		
		sound2 = myIntake->lastOutL;

		left = sound1 * 0.7 + sound2;
		right = sound2 * 0.7 + sound1;

    // DC offset and speaker protection
		left = myHPL->tickHP(left);
		right = myHPR->tickHP(right);

		myLimiter->tick(&left,&right);		

		*pDataL++ = left;
		*pDataR++ = right;
		length_samples--;
	}
}


void Synth::synthRenderBytes(unsigned char* pByteDataL, unsigned char* pByteDataR, DWORD length_samples) {

	float* lSrc = pDataL;
	float* rSrc = pDataR;

	synthRender(pDataL,pDataR,length_samples);

	WORD* lDest = (WORD*)pByteDataL;
	WORD* rDest = (WORD*)pByteDataR;

	while(length_samples--) {
		*lDest++ = Dither(lSrc++); 
		*rDest++ = Dither(rSrc++); 
	}

}

void Synth::synthRenderBytesCombined(unsigned char* pByteData, DWORD length_samples) {

	float* lSrc = pDataL;
	float* rSrc = pDataR;

	synthRender(pDataL,pDataR,length_samples);

	DWORD* b = (DWORD*)pByteData;

	while(length_samples--) {
		*b++ = (Dither(lSrc++) << 16) + (Dither(rSrc++)); 
	}

}





void Synth::setRPM(float rpm) {
	myEngine->setRPM(rpm);
}

void Synth::setThrottle(float throttle) {
	myEngine->setThrottle(throttle);
}

void Synth::setIgnition(bool ignition) {
	myEngine->setIgnition(ignition);
}

float Synth::getProbe(int probeId) {
	switch(probeId) {
		case 0: return myEngine->myInVents[0]->K / myEngine->myInVents[0]->Qmax;
		case 1: return myEngine->myOutVents[0]->K / myEngine->myOutVents[0]->Qmax;		
		case 2: return myEngine->myCyls[0]->phase;
		case 3: return myEngine->myCyls[0]->x * 100;
		case 4: return myEngine->myCyls[0]->P;
	}
	return 0;
}

void Synth::unclick() {
	myEngine->params->unclick();
	myExhaust->params->unclick();
	myIntake->params->unclick();	
}

void Synth::click(int x, int y) {
	myEngine->params->click(x,y);
	myExhaust->params->click(x,y);
	myIntake->params->click(x,y);
}

void Synth::move(int x, int y) {
	myEngine->params->move(x,y);
	myExhaust->params->move(x,y);
	myIntake->params->move(x,y);
}

void Synth::draw(HDC hdc) {
	myEngine->params->draw(hdc);
	myExhaust->params->draw(hdc);
	myIntake->params->draw(hdc);
}



