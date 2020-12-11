#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_out.h"

using namespace std;


void Gate_out::calc_and_affect(){
  if (this->nb_entry_rdy >= this->nb_of_entry){     //la porte est à calculer?
    cout << "Sortie" << this->nom << "stable";
  }
}
