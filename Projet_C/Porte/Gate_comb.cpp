#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "Gate_mux.h"

using namespace std;


void Gate_comb::calc_and_affect(){
  cout << "this->getName() " << this->getName() << endl;
  cout << "this->nb_entry_rdy " << this->nb_entry_rdy << endl;
  cout << "this->nb_of_entry " << this->nb_of_entry << endl;
  if (this->nb_entry_rdy == this->nb_of_entry){     //la porte est à calculer?
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
    //Affectation du resulat aux portes suivantes
    for(unsigned i = 0; i < this->output.size(); i++){
      if(this->output.at(i)->get_is_a_mux()){
        this->output.at(i)->update_mux(res, this->output.at(i)->getName()) ;
      }
      else{
        this->output.at(i)->update_input(res);
      }
      // this->output.at(i)->update_input(res);
    }
    this->nb_entry_rdy = 0; //Reset du nombre d'entrée actualisé
  }
}

void Gate_comb::update_mux(int n, string s){
  cout << "Fonction vide update_mux de comb" << endl;
}
