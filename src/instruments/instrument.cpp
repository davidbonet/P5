#include <iostream>
#include "instrument_dumb.h"
#include "seno.h"
#include "vibratoFM.h"
#include "tablaext.h"
#include "samplers.h"

/*
  For each new instrument:
  - Add the header in this file
  - Add the call to the constructor in get_instrument() (also in this file)
  - Add the source file to src/meson.build
*/

using namespace std;

namespace upc {
  Instrument * get_instrument(const string &name,
			      const string &parameters) {
    Instrument * pInst = 0;
    //    cout << name << ": " << parameters << endl;
    if (name == "InstrumentDumb")
      pInst = (Instrument *) new InstrumentDumb(parameters);
    if (name == "Seno")
      pInst = (Instrument *) new Seno(parameters);
    if (name == "VibratoFM")
      pInst = (Instrument *) new VibratoFM(parameters);
    if (name == "TablaExt")
      pInst = (Instrument *) new TablaExt(parameters);
    if (name == "Samplers")
      pInst = (Instrument *) new Samplers(parameters);
    return pInst;
  }
}
