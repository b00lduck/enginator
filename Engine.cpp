#include "engine.h"
#include "Zylinder.h"
#include "Ventil.h"

char *motortyp[ENGINETYPES] = {"R3","R4","R6","V8"};

int et[ENGINETYPES] = {ENGINETYPE_R3,ENGINETYPE_R4,ENGINETYPE_R6,ENGINETYPE_V8};

Engine::Engine() {
	params = new EngineSettings(this);
	params->load("engine.params");
	phase = 0;
	ignition = true;
    throttle = 0;
	rpm = 750;
	throttleFilter = new LPFilt(0.001,1,1);
	int i;
	for (i=0;i<MAXCYLS;i++) {
		myCyls[i] = new Zylinder(0.07,0.08,7,0.15,0.04, 1, 1, this);					
		myOutVents[i] = new Ventil(540,719,_P(PARAM_ENG_OUT_SH),_P(PARAM_ENG_OUT_Q),this);
		myInVents[i] =  new Ventil(0,180,_P(PARAM_ENG_IN_SH),_P(PARAM_ENG_IN_Q),this);
	}
	
	setEngineType(_P(PARAM_ENG_TYPE));

	exhaust_noise = new Noise();
	intake_noise = new Noise();
}

Engine::~Engine() {
  params->save("engine.params");
	SAFE_DELETE(params);
	for (int i=0;i<MAXCYLS;i++) {
		SAFE_DELETE(myCyls[i]);
		SAFE_DELETE(myOutVents[i]);
		SAFE_DELETE(myInVents[i]);	
	}
}

void Engine::setEngineType(int engtype) {
	if ((engtype < 0) || (engtype >= ENGINETYPES)) engtype = 0;
	type = et[engtype];
	setCyls (et[engtype] & 0xff);
	is_v = (et[engtype] & 0xff00) >> 8;
}

void Engine::setCyls(int cyls) {
	this->cyls = cyls;
	for (int i=0;i<cyls;i++) {
		float offset = i*PI*4/(float)cyls;
		myCyls[i]->setOffset(offset);			
		myOutVents[i]->setOffset(offset);
		myInVents[i]->setOffset(offset);
	 }						 
}

float Engine::move() {
	float dp = rpm * PI * 2 / (SAMPLERATE * 60.0f);
	phase += dp;
	if (phase >= PI4) phase -= PI4;	
	for (int i=0;i<cyls;i++) {		
		myCyls[i]->move(dp);
		myOutVents[i]->move(dp);
		myInVents[i]->move(dp);
	}
	return dp;
}

void Engine::setThrottle(float throttle) {
	this->throttle = throttle;	
}

float Engine::getThrottle() {
	return throttle;
}

void Engine::setRPM(float rpm) {
	this->rpm = rpm;	
}

void Engine::setIgnition(bool ignition) {
	this->ignition = ignition;	
}

void Engine::process() {

	float filteredThrottle = throttleFilter->tick(throttle);
	if (filteredThrottle < 0.01) filteredThrottle = 0;

	for (int i=0;i<cyls;i++) {
		
		Zylinder *myZ = (Zylinder*) myCyls[i];
		Ventil *myVout = (Ventil*) myOutVents[i];
		Ventil *myVin = (Ventil*) myInVents[i];
			
		myVin->Qmax = (filteredThrottle * _P(PARAM_ENG_IN_Q));					
		myVout->Qmax = (_P(PARAM_ENG_OUT_Q));
		myVout->sharpness = _P(PARAM_ENG_OUT_SH);
		myVin->sharpness = _P(PARAM_ENG_IN_SH);

		exhaust[i] = myZ->setdPout(myVout->K);
		intake[i]  = myZ->setdPin(myVin->K);

		exhaust[i] = (exhaust[i]*exhaust_noise->tick()*_P(PARAM_ENG_NOISE)) + (exhaust[i]);
  		intake[i] = (intake[i]*intake_noise->tick()*_P(PARAM_ENG_NOISE)) + (intake[i]);
	}

}

