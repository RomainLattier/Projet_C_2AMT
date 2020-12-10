#ifndef _OR_H_
#define _OR_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"

using namespace std;

class Or : public virtual Gate_comb {

private:


public:

  Or(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte Or " << nom <<  endl;
  }

  ~Or(){
    cout << "Destruction de la porte Or " << nom << endl;
  }

  int operation(const int & a, const int & b);

};

#endif
