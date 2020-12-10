#ifndef _INV_H_
#define _INV_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "../Gate.h"
#include "../Gate_comb.h"

using namespace std;

class Inv : public virtual Gate_comb {

private:


public:

  Inv(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte Inv " << nom <<  endl;
  }

  ~Inv(){
    cout << "Destruction de la porte Inv " << nom << endl;
  }

  int operation(const int & a, const int & b = 0);

};

#endif
