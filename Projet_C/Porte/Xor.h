#ifndef _XOR_H_
#define _XOR_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"

using namespace std;

class Xor : public virtual Gate_comb {

private:


public:

  Xor(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte Xor " << nom <<  endl;
  }

  ~Xor(){
    cout << "Destruction de la porte Xor " << nom << endl;
  }

  int operation(const int & a, const int & b);

};

#endif
