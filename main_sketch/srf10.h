#ifndef srf10_H
#define srf10_H

#include "Arduino.h"

class srf10 {
public:
  srf10();
  ~srf10();
  byte ping(byte address);
};

#endif
