#include <iostream>
#include <math.h>
#include "seno.h"
#include "keyvalue.h"
#include <stdlib.h>

using namespace upc;
using namespace std;

Seno::Seno(const std::string &param) 
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
  
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  phase = 0, step = 2 * M_PI /(float) N;
  index_aux = 0.0F;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += step;
  }
}


void Seno::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
	  A = vel / 127.;
    float f0 = pow(2, (float) (note - 69)/12) * 440;
    step_note = 2 * M_PI /(float) (SamplingRate / f0);
  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}

const vector<float> & Seno::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;
  float alpha, beta; 
  for (unsigned int i=0; i<x.size(); ++i) {
    if(index_aux == round(index_aux)) {
      x[i] = A * tbl[index_aux];
    } else {
      index_pre  = floor(index_aux);
      index_post = ceil(index_aux);
      alpha = index_aux - index_pre;
      beta  = index_post - index_aux;
      if(index_post == tbl.size()) {
        index_post = 0;
        beta = tbl.size() - index_aux;
      }
      x[i] = A * (tbl[index_pre]*beta + tbl[index_post]*alpha);
    }
    index_aux += step_note / step;

    if(index_aux >= tbl.size())
      index_aux = index_aux - tbl.size();
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
