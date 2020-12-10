#ifndef _XNOR_H_
#define _XNOR_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"

using namespace std;

class Xnor : public virtual Gate_comb {

private:


public:

  Xnor(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte Xnor " << nom <<  endl;
  }

  ~Xnor(){
    cout << "Destruction de la porte Xnor " << nom << endl;
  }

  int operation(const int & a, const int & b);

};

#endif
