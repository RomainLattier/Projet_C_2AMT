#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_mux.h"

using namespace std;


void Gate_mux::calc_and_affect(){
  if (this->nb_entry_rdy == this->nb_of_entry){     //la porte est à calculer?
    int res;


    //Affectation du resulat aux portes suivantes
    for(unsigned i = 0; i < this->output.size(); i++){
      // cout << "res " << res << endl << endl;
      // cout << "output.at(i).getName() " << output.at(i)->getName() << endl << endl;
      if( (this->output.at(i)->get_is_a_mux()) && (this->getName() == this->output.at(i)->get_sel_gate_name()) ){ //cas special des mux
        this->output.at(i)->set_sel(res);
      }
      else{
        this->output.at(i)->update_input(res);
      }
    }
    this->nb_entry_rdy = 0; //Reset du nombre d'entrée actualisé
  }
}
