#include "Exhaust.h"

Exhaust::Exhaust() {
    this->params = new ExhaustSettings(this);	
    params->load("exhaust.params");
    exnoise1 = new Noise();
    myWaveguide = NULL;
}

Exhaust::~Exhaust() {
    params->save("exhaust.params");
    SAFE_DELETE(params);
    SAFE_DELETE(myWaveguide);
}

void Exhaust::process(float input) {

    if (params->changed) {
        setPipes();
        params->changed = false;
    }

    float in = input;
    lastOutL = myWaveguide->process(in,0.5);
    lastOutL *= _P(PARAM_EXH_GAIN);
    		
}

void Exhaust::setPipes() {
    SAFE_DELETE(myWaveguide);
    myWaveguide = new perfWaveGuide(_P(PARAM_EXH_GESLAENGE));
    myWaveguide->setEndFB(_P(PARAM_EXH_ENDFB_ORDER),_P(PARAM_EXH_ENDFB_CUTOFF),_P(PARAM_EXH_ENDFB_GAIN));
    myWaveguide->setTubeFilt(_P(PARAM_EXH_TUBE_ORDER),_P(PARAM_EXH_TUBE_CUTOFF),_P(PARAM_EXH_TUBE_GAIN));
    myWaveguide->addNormalizedJunction(_P(PARAM_EXH_SS1), 1,1,_P(PARAM_EXH_SS1k1));
    myWaveguide->addNormalizedJunction(_P(PARAM_EXH_SS2), 1,1,_P(PARAM_EXH_SS2k1));
    myWaveguide->addNormalizedJunction(_P(PARAM_EXH_SS3), 1,1,_P(PARAM_EXH_SS3k1));
    myWaveguide->addNormalizedJunction(_P(PARAM_EXH_SS4), 1,1,_P(PARAM_EXH_SS4k1));
	myWaveguide->setNoiseFactor(_P(PARAM_EXH_TUBE_NOISE));
}

void bubbleSort (int list[], float list1[], int len) {    
    // sorts 2 arrays by the first
    int sorted = FALSE;
    while (!sorted) {
        int j;
        sorted = TRUE;
        for (j = 0; j < len - 1; j++) {
            if (list[j] > list[j + 1]) {
                int t,u;
                sorted = FALSE;
                t = list[j];
				        u = list1[j];
                list[j] = list[j + 1];
				        list1[j] = list1[j + 1];
                list[j + 1] = t;
				        list1[j + 1] = u;
			      }
		    }
	  }
}