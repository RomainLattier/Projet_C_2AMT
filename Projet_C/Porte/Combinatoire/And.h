#ifndef _AND_H_
#define _AND_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"

using namespace std;

class And : public virtual Gate_comb {

private:


public:

  And(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte And " << nom <<  endl;
  }

  ~And(){
    cout << "Destruction de la porte And " << nom << endl;
  }

  int operation(const int & a, const int & b);

};

#endif
