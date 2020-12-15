#ifndef _GATE_MUX_H_
#define _GATE_MUX_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_mux : public virtual Gate {

private:
  Gate* sel_gate;
  int sel;

public:

  Gate_mux(string name, int nb_entry):Gate(name,nb_entry){
    cout << "Creation d'une porte mux " << nom << endl;
  }

  virtual ~Gate_mux(){
    cout << "Destruction de la porte mux " << nom << endl;
  }

  string get_sel_gate_name(){
    return sel_gate->getName();
  }

  void set_sel(int n){
    sel = n;
  }

  void calc_and_affect();

};

#endif
