#ifndef _GATE_MUX_H_
#define _GATE_MUX_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

class Gate_mux : public virtual Gate {

private:
  vector<string> sel_name; //Nom des entre de sel le 1er dans le vector est le 1er à gauche sur la ligne
  vector<string> gate_input; //Nom des entre de gate le 1er dans le vector est le 1er recontrer dans le fichier
  vector<int> sel_value; //Stocke les valeurs des sel

public:

  Gate_mux(string name, int nb_entry, int nb_sel):Gate(name,nb_entry){
    cout << "Creation d'une porte mux " << nom << endl;
    for(int i = 0; i<nb_sel;i++){
      set_value.push_back(0);
    }
  }

  virtual ~Gate_mux(){
    cout << "Destruction de la porte mux " << nom << endl;
  }

  void calc_and_affect();

  void update_mux(int n, string s);

};

#endif
