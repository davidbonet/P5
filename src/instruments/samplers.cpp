#include <iostream>
#include <math.h>

#include <errno.h>
#include <string.h>

#include "samplers.h"
#include "keyvalue.h"
#include "wavfile_mono.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

Samplers::Samplers(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  KeyValue kv(param);
  int N;
  std::string file_name;
  static string kv_null;
  
  if ((file_name = kv("file")) == kv_null) {
    cerr << "Error: no se ha encontrado el campo con el fichero de la señal para ··· 􏰄→ un instrumento FicTabla" << endl;
    throw -1; 
  }
  
  unsigned int fm;
  if (readwav_mono(file_name, fm, tbl) < 0) {
    cerr << "Error: no se puede leer el fichero " << file_name << " para un ··· 􏰄→ instrumento FicTabla" << endl;
    throw -1; 
  }
  N = tbl.size();
  step = 2 * M_PI /(float) N;
  index_aux = 0.0F;
}


void Samplers::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
	  A = vel / 127.;
    float f0 = pow(2, (float) (note - 69)/12) * 440;
    step_note = 2 * M_PI /(float) (SamplingRate / f0);
  }
  /*
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
  */
}


const vector<float> & Samplers::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;
  float alpha, beta; 
  for (unsigned int i=0; i<x.size(); ++i) {
    if (index_aux <= tbl.size()) {
      x[i] = A * tbl[index_aux++];
    } else {
      x[i] = 0;
      adsr.end();
    }
    
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
