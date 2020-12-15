#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>

#include "Gate.h"
#include "Gate_mux.h"

using namespace std;


void Gate_mux::calc_and_affect(){
  if (this->nb_entry_rdy == this->nb_of_entry + this->sel_name.size()){     //la porte est à calculer?
    int entry_nb = 0;
    for(unsigned i = 0; i < this->sel_value.size(); i++){
      entry_nb = entry_nb + pow(2,i);
    }
    int res = this->input.at(entry_nb);

    //Affectation du resulat aux portes suivantes
    for(unsigned i = 0; i < this->output.size(); i++){
      if(this->output.at(i)->get_is_a_mux()){
        this->output.at(i)->update_mux(res, this->output.at(i)->getName()) ;
      }
      else{
        this->output.at(i)->update_input(res);
      }
    }
    this->nb_entry_rdy = 0; //Reset du nombre d'entrée actualisé
  }
}

void Gate_mux::update_mux(int n, string s){
  int hit = 0;
  int index;
  for (unsigned i = 0; i<this->gate_input.size(); i++){
    if(this->gate_input.at(i) == s){
      hit = 1;
      index = i;
    }
  }
  if(!hit){
    for(unsigned i = 0; i<this->sel_name.size(); i++){
      if(this->sel_name.at(i) == s){
        hit = 2;
        index = i;
      }
    }
  }
  switch (hit) {
    case 0: cout << "Erreur hit Mux" << endl;
            break;
    case 1: this->input.at(index) = n;
            this->add_nb_entry_rdy();
            break;
    case 2: this->sel_value.at(index) = n;
            this->add_nb_entry_rdy();
            break;
    default: cout << "Default de Mux" << endl;
            break;
  }
}
