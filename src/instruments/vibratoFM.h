#ifndef VIBRATOFM
#define VIBRATOFM

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"
#include <errno.h>

namespace upc {
  class VibratoFM: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index_pre, index_post;
	  float A, phase, step, step_note1, index_aux;
      float N1;
      float N2;
      float I;
      float fm;
      float step_note2;
      float phase1;
      float phase2;

    std::vector<float> tbl;
  public:
    VibratoFM(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif
