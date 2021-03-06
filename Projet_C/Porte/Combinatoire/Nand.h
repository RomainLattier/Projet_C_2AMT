#ifndef _NAND_H_
#define _NAND_H_

#include <iostream>
#include <string.h>
#include <vector>

#include "../Gate.h"
#include "../Gate_comb.h"

using namespace std;

class Nand : public virtual Gate_comb {

private:


public:

  Nand(string nom, int nb_of_entry):Gate(nom,nb_of_entry),Gate_comb(nom,nb_of_entry){
    cout << "Creation de la porte Nand " << nom <<  endl;
  }

  ~Nand(){
    cout << "Destruction de la porte Nand " << nom << endl;
  }

  int operation(const int & a, const int & b);

};

#endif
