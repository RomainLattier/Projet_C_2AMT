#ifndef _GATE_MUX_H_
#define _GATE_MUX_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_mux : public virtual Gate {

private:
  vector<string> sel_name;
  vector<string> gate_input;
  vector<int> sel_value;

public:

  Gate_mux(string name, int nb_entry):Gate(name,nb_entry){
    cout << "Creation d'une porte mux " << nom << endl;
  }

  virtual ~Gate_mux(){
    cout << "Destruction de la porte mux " << nom << endl;
  }

  void calc_and_affect();

  void update_mux(int n, string s);

};

#endif
