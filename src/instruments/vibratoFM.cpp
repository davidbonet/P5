#include <iostream>
#include <math.h>
#include "vibratoFM.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

VibratoFM::VibratoFM(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);
  int N;

  if (!kv.to_int("N",N))
    N = 40; //default value

    if (!kv.to_float("N1",N1))
    N1 = 5; //default value
  if (!kv.to_float("N2",N2))
    N2 = 6; //default value
  if (!kv.to_float("I",I))
    I = 1; //default value
  I = 1. - pow(2, -I / 12.);
  
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  phase = 0, step = 2 * M_PI /(float) N;
  index_aux = 0.0F;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += step;
  }
}


void VibratoFM::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
	  A = vel / 127.;
    float fc = pow(2, (float) (note - 69)/12) * 440;
    fm = (N2/N1) * (fc/SamplingRate);

    step_note1 = 2 * M_PI /(float) (SamplingRate / fc);
    step_note2 = 2 * M_PI * fm;
    phase = 0;
    phase1 = 0;
    phase2 = 0;

  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & VibratoFM::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;
  float alpha, beta; 
  for (unsigned int i=0; i<x.size(); ++i) {


      x[i] = A * sin(phase1 + I * sin(phase2));

      phase1 = phase1 + step_note1;
      while(phase1 >= 2 * M_PI){
          phase1 -= 2 * M_PI;
      }

      phase2 = phase2 + step_note2;
      while(phase2 >= 2 * M_PI){
          phase2 -= 2 * M_PI;
      }
  }
    
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
