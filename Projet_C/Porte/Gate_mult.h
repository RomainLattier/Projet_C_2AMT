#ifndef _GATE_MULT_H_
#define _GATE_MULT_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_mult : public virtual Gate {

private:
  Gate* sel_gate;
  int sel;

public:

  Gate_mult(string name, int nb_entry):Gate(name,nb_entry){
    cout << "Creation d'une porte mux " << nom << endl;
  }

  virtual ~Gate_mult(){
    cout << "Destruction de la porte mux " << nom << endl;
  }

  void calc_and_affect();

};

#endif
