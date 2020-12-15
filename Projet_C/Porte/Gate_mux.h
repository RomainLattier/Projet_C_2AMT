#ifndef _GATE_MUX_H_
#define _GATE_MUX_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_mux : public virtual Gate {

private:
  

public:

  Gate_mux(string name, int nb_entry, int nb_sel):Gate(name,nb_entry){
    cout << "Creation d'une porte mux " << nom << endl;
    for(int i = 0; i<nb_sel;i++){
      sel_value.push_back(0);
    }
  }

  virtual ~Gate_mux(){
    cout << "Destruction de la porte mux " << nom << endl;
  }

  void calc_and_affect();

  void add_sel_name(string s){
    sel_name.push_back(s);
  }

  void add_gate_input(string s){
    gate_input.push_back(s);
  }

  void update_mux(int n, string s);

};

#endif
