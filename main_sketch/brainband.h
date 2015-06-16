#ifndef brainband_H
#define brainband_H

#include "Arduino.h"

class brainband {
public:
  brainband();
  ~brainband();
  byte ReadOnce();
  unsigned int getAtt();
  unsigned int getMed();
};

#endif
