#include "Intake.h"

Intake::Intake() {
	this->params = new IntakeParams(this);
	params->load("intake.params");
	myWaveguide = NULL;
}

Intake::~Intake() {
  params->save("intake.params");
	SAFE_DELETE(params);
	SAFE_DELETE(myWaveguide);
}


void Intake::process(float input) {

	if (params->changed) {
		setPipes();
		params->changed = false;
	}

	float in = input;

	lastOutL = myWaveguide->process(in);
	lastOutR = lastOutL;
	lastOutL *= _P(PARAM_INT_GAIN);
	lastOutR *= _P(PARAM_INT_GAIN);
		
}

void Intake::setPipes() {

	SAFE_DELETE(myWaveguide);
	myWaveguide = new perfWaveGuide(_P(PARAM_INT_GESLAENGE));
	myWaveguide->setEndFB(_P(PARAM_INT_ENDFB_ORDER),_P(PARAM_INT_ENDFB_CUTOFF),_P(PARAM_INT_ENDFB_GAIN));
	myWaveguide->setTubeFilt(_P(PARAM_INT_TUBE_ORDER),_P(PARAM_INT_TUBE_CUTOFF),_P(PARAM_INT_TUBE_GAIN));
	myWaveguide->addNormalizedJunction(_P(PARAM_INT_SS1), 1,0.1,_P(PARAM_INT_SS1k1));
	myWaveguide->addNormalizedJunction(_P(PARAM_INT_SS2), 1,0.1,_P(PARAM_INT_SS2k1));
	myWaveguide->addNormalizedJunction(_P(PARAM_INT_SS3), 1,0.1,_P(PARAM_INT_SS3k1));
	myWaveguide->addNormalizedJunction(_P(PARAM_INT_SS4), 1,0.1,_P(PARAM_INT_SS4k1));
}








