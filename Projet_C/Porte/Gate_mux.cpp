#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>

#include "Gate.h"
#include "Gate_mux.h"

using namespace std;


void Gate_mux::calc_and_affect(){
  cout << "gate_mux" << endl;
  cout << "this->getName() " << this->getName() << endl;
  cout << "this->nb_entry_rdy " << this->nb_entry_rdy << endl;
  cout << "this->nb_of_entry " << this->nb_of_entry << endl;
  cout << "this->sel_name.size() " << this->sel_name.size() << endl;
  if (this->nb_entry_rdy == this->nb_of_entry + this->sel_name.size()){     //la porte est à calculer?
    int entry_nb = 0;
    for(unsigned i = 0; i < this->sel_value.size(); i++){
      if(sel_value.at(i)){
        entry_nb = entry_nb + pow(2,i);
      }
    }
    // cout << "calcul de l'entre via sel " << entry_nb << endl;
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
  // cout << "nom de l'entre dans update mux " << s << endl;
  for (unsigned i = 0; i<this->gate_input.size(); i++){ //On cherchie si c'est une entre
    // cout << "Nom des entre dans mux " << this->gate_input.at(i) << endl;
    if(this->gate_input.at(i) == s){
      hit = 1;
      index = i;
    }
  }
  if(!hit){
    for(unsigned i = 0; i<this->sel_name.size(); i++){ //On cherche si c'est une sel
      if(this->sel_name.at(i) == s){
        hit = 2;
        index = i;
      }
    }
  }
  // cout << "valeur de hit " << hit << endl;
  // cout << "valeur de index " << index << endl;
  switch (hit) {
    case 0: cout << "Erreur hit Mux" << endl;
            break;
    case 1: this->input.at(index) = n; //attribution a la bonne entre
            this->add_nb_entry_rdy();
            break;
    case 2: this->sel_value.at(index) = n; //attribution au bon sel
            this->add_nb_entry_rdy();
            break;
    default: cout << "Default de Mux" << endl;
            break;
  }
}
