#ifndef _GATE_OUT_H_
#define _GATE_OUT_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_out : public virtual Gate {

private:


public:

  Gate_out(string name, int nb_entry):Gate(name,nb_entry){
    cout << "Creation d'une porte tampon de sortie " << nom << endl;
  }

  virtual ~Gate_out(){
    cout << "Destruction de la porte tampon de sort " << nom << endl;
  }

  void update_mux(int n, string s);

  bool calc_and_affect();

};

#endif
