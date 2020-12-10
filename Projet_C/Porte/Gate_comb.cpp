#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"

using namespace std;


void Gate_comb::calc_and_affect(){
  if (this->nb_entry_rdy == this->nb_of_entry){     //la porte est à calculer?
    int res = this->operation(this->input.at(0), this->input.at(1)); //calcul de la premiere valeur

    //si il y a plusieurs entrée on fait des calculs en chaine pour avoir le dernier resultat
    if(this->input.size() > 2){
      for(unsigned i = 2; i < this->input.size(); i++){
        res = this->operation(this->input.at(i), res);
      }
    }
    //Affectation du resulat aux portes suivantes
    for(unsigned i = 0; i < this->output.size(); i++){
      this->output.at(i)->update_input(res);
    }
    /*for(vector<Gate*>::iterator it_affect = this->output.begin(); it_affect != this->output.end(); ++it_affect){
        it_affect->update_intput(res);
    }*/
    this->nb_entry_rdy = 0; //Reset du nombre d'entrée actualisé
  }
}
