#include "Noise.h"

Noise::Noise() {
  b0 = b1 = b2 = b3 = b4 = b5 = b6 = 0;
}

float Noise::tick() {
  float white = (rand() / (float)RAND_MAX) * 2 - 1;

  b0 = 0.99886f * b0 + white * 0.0555179f;
  b1 = 0.99332f * b1 + white * 0.0750759f;
  b2 = 0.96900f * b2 + white * 0.1538520f;
  b3 = 0.86650f * b3 + white * 0.3104856f;
  b4 = 0.55000f * b4 + white * 0.5329522f; 
  b5 = -0.7616f * b5 - white * 0.0168980f;

  // saved one division
  float out = 0.5f + (b0 + b1 + b2 + b3 + b4 + b5 + b6 + white * 0.5362f) / 16.0f;
  b6 = white * 0.115926f;
  return out; 

}


 

