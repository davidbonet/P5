#ifndef CHORUS_H
#define CHORUS_H

#include <vector>
#include <string>
#include "effect.h"

namespace upc {
  class Chorus: public upc::Effect {
    private:
	  std::vector<float> buffer;
	  float	T;
    int retard;
    public:
      Chorus(const std::string &param = "");
	  void operator()(std::vector<float> &x);
	  void command(unsigned int);
  };
}

#endif
