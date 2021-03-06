#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "Gate_mux.h"

using namespace std;


bool Gate_comb::calc_and_affect(){
  // cout << "this->getName()" << this->getName()<< endl;
  for(unsigned i = 0; i < this->output.size(); i++){
    this->output.at(i)->add_antescedant(this->getName(), this->antescedant);
    if(this->rebouclage(output.at(i)->getName())){
      cout << "erreur de rebouclage" << endl;
      return 1;
    }
  }
  // cout << "gate_comb" << endl;
  // cout << "this->getName() " << this->getName() << endl;
  // cout << "this->nb_entry_rdy " << this->nb_entry_rdy << endl;
  // cout << "this->nb_of_entry " << this->nb_of_entry << endl;
  if (this->nb_entry_rdy == this->nb_of_entry){     //la porte est à calculer?
    // cout << "calcul de gate_comb " << endl;
    int res;
    if(this->nb_of_entry == 1){
      res = this->operation(this->input.at(0),0); //Cas particulier des inverseurs
    }
    else{
      res = this->operation(this->input.at(0), this->input.at(1)); //calcul de la premiere valeur
    }
    //si il y a plusieurs entrée on fait des calculs en chaine pour avoir le dernier resultat
    if(this->input.size() > 2){
      for(unsigned i = 2; i < this->input.size(); i++){
        res = this->operation(this->input.at(i), res);
      }
    }
    // cout << "gate_comb calculer " << endl;
    // cout << "this->output.size() " << this->output.size() << endl;
    //Affectation du resulat aux portes suivantes
    for(unsigned i = 0; i < this->output.size(); i++){
      if(this->output.at(i)->get_is_a_mux()){
        // cout << "le prochain est un mux" << endl;
        this->output.at(i)->update_mux(res, this->getName()) ;
      }
      else{
        // cout << "le suivant c'est pas un mux" << endl;
        this->output.at(i)->update_input(res);
      }
      // this->output.at(i)->update_input(res);
    }
    this->nb_entry_rdy = 0; //Reset du nombre d'entrée actualisé
  }
  return 0;
}

void Gate_comb::update_mux(int n, string s){
  cout << "Fonction vide update_mux de comb" << endl;
}
