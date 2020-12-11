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

int Gate_out::is_stable(){
  return this->nb_entry_rdy >= this->nb_of_entry;
}

int Gate_out::getValueAndReset(){
  this->nb_entry_rdy == 0;
  return this->input.at(0);
}
