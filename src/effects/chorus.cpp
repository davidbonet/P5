#include <iostream>
#include <math.h>
#include "chorus.h"
#include "keyvalue.h"
#include "instrument.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

Chorus::Chorus(const std::string &param) {
  KeyValue kv(param);

  // I is the maximum downward pitch shift in semitones
  // As the shift is sinusoidal, the maximum posible shift is 2 (one octave)
  // In this way, we prevent negative shifts
  if (!kv.to_float("T", T))
    T = 0.05; //default

  retard = 5;
}

void Chorus::command(unsigned int cmd) {
}

void Chorus::operator()(std::vector<float> &x){
  for (unsigned int i = retard; i < x.size(); i++) {
    x[i] = 0;
  }
}