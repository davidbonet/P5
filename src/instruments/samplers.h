#ifndef SAMPLERS
#define SAMPLERS

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class Samplers: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index_pre, index_post;
	  float A, step, step_note, index_aux;
    std::vector<float> tbl;
  public:
    Samplers(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif
