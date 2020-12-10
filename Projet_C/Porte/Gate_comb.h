#ifndef _GATE_COMB_H_
#define _GATE_COMB_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_comb : public virtual Gate {

private:


public:

  Gate_comb(string name, int nb_entry):Gate(name,nb_entry){}

  virtual ~Gate_comb(){}

  void calc_and_affect();

  virtual int operation(const int & a, const int & b) = 0;

};

#endif
