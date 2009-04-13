#include "Synth.h"

Synth* g_pSynth = NULL;

Synth::Synth() {

  g_pSynth = this;

  myEngine = new Engine();
  myIntake = new Intake();
  myExhaust1 = new Exhaust();
  myExhaust2 = new Exhaust();

  myHPL = new IIR();
  myHPR = new IIR();
  myHPL->setLowpass(1,0.1,1);
  myHPR->setLowpass(1,0.1,1);
  //Limiter: float thresh,float slope,float tla,float twnd,float tatt,float trel
  myLimiter = new Limiter(0.9,0.01,5);

}

Synth::~Synth() {

	SAFE_DELETE(myIntake);
	SAFE_DELETE(myExhaust1);
	SAFE_DELETE(myExhaust2);
	SAFE_DELETE(myEngine);
	
	SAFE_DELETE(myHPL);
	SAFE_DELETE(myHPR);
	SAFE_DELETE(myLimiter);
}

void Synth::synthRender(float* pDataL, float* pDataR, DWORD length_samples) {

	while (length_samples > 0) {
		float sound1 = 0;		
		float sound2 = 0;
			
		myEngine->move();	
		myEngine->process();		
			
		int banks[8] = { 0, 1, 1, 1 , 0, 1, 0, 0 };
		
		float engineout1 = 0;
		float engineout2 = 0;
		float enginein = 0;
		
		for(int i=0;i<myEngine->cyls;i++) {
		
			switch (banks[i]) {
				case 0:	engineout1 += myEngine->exhaust[i]; break;
				case 1: engineout2 += myEngine->exhaust[i]; break;
				case 2: engineout1 += myEngine->exhaust[i];
						engineout2 += myEngine->exhaust[i];
			}
			
		  enginein += myEngine->intake[i] * (0.5 + i/4.0f);

		}

		myIntake->process(enginein);		
		myExhaust1->process(engineout1 + engineout2 * 0.75);
		//myExhaust2->process(engineout2);

		left = right = 0;
		
		sound1 = myExhaust1->lastOutL;
		//sound1 = myExhaust2->lastOutL * 0.75;
		
		sound2 = myIntake->lastOutL;
		//sound2 += myIntake->lastOutR;

		left = sound1 + sound2;
		right = left        ;

    // DC offset and speaker protection
		left = myHPL->tickHP(left);
		right = myHPR->tickHP(right);

		myLimiter->tick(&left,&right);		

		*pDataL++ = left;
		*pDataR++ = right;
		length_samples--;
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