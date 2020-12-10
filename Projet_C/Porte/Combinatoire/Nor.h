#ifndef _NOR_H_
#define _NOR_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "../Gate.h"
#include "../Gate_comb.h"

using namespace std;

class Nor : public virtual Gate_comb {

private:


public:

  Nor(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte Nor " << nom <<  endl;
  }

  ~Nor(){
    cout << "Destruction de la porte Nor " << nom << endl;
  }

  int operation(const int & a, const int & b);

};

#endif
