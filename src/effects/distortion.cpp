#include <iostream>
#include <math.h>
#include "distortion.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

Distortion::Distortion(const std::string &param) {

  KeyValue kv(param);

  if (!kv.to_float("th", th))
    th = 0.5; //default value
}

void Distortion::command(unsigned int comm) {

}

void Distortion::operator()(std::vector<float> &x){
  for (unsigned int i = 0; i < x.size(); i++) {
    if(x[i] > th) x[i] = 1;
    else if(x[i] < -th) x[i] = -1;
  }
}
