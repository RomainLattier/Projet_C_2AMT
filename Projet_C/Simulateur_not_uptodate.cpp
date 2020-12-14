#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

//include des Parser
#include "/Parser_gate/Parser_gate.h"

//include des gate
#include "../Porte/Gate.h"

#include "../Porte/Gate_comb.h"
#include "../Porte/Combinatoire/And.h"
#include "../Porte/Combinatoire/Inv.h"
#include "../Porte/Combinatoire/Or.h"
#include "../Porte/Combinatoire/Nand.h"
#include "../Porte/Combinatoire/Nor.h"
#include "../Porte/Combinatoire/Xor.h"
#include "../Porte/Combinatoire/Xnor.h"

#include "../Porte/Gate_out.h"

int main(){
  map<string,vector<Gate *> > m_input; //map des entres du circuit
  map<string,vector<int> > m_output; //map des sorties du circuit
  vector<Gate *> v_output_tampon; //map des gate tampon de sortie
  vector<Gate *> v_gate_all; //vector des gates du ciruit
  vector<string> v_input; //vector des clé entrés
  vector<string> v_output; //vector des clé sorties

  map<string,vector<int> > m_stimulis; //map des différents stimuls clé = entrée vector = valeur
  vector<int> v_duree_delta; //vector de la duréee de chaque stimulis

  //Appel du parser gate


  //Appel du parser simu

  //Simulation
  //Premiere update des entree
  cout << "avant 1er update" << endl;
  unsigned it_delta_cycle = 0; //indice du delta_cycle
  for(unsigned i = 0; i<v_input.size(); i++){ //on parcourt la liste v_input pour recuper les clés d'input
    for(unsigned j = 0; j<m_input[v_input.at(i)].size(); j++){ //on parcourt le vecteur correspondant à la clé
      m_input[v_input.at(i)].at(j)->update_input(m_stimulis[v_input.at(i)].at(it_delta_cycle)); //on update chaque gate avec la nouvelle valeur de stimulis
    }
  }
  cout << "apres 1er update" << endl;

  //Boucle de simu

  while (it_delta_cycle < v_duree_delta.size()) {
    int stab = 1;
    for(unsigned i = 0; i<v_output_tampon.size(); i++){ //recherche si la simu pour ce delta est fini
      if(!v_output_tampon.at(i)->is_stable()){
        stab = 0;
      }
    }

    cout << "stab apres check update " << stab <<endl;
    cout << "it_delta_cycle " << it_delta_cycle << endl;
    if(stab){
      cout << "recup des sorties" << endl;
      //Recuperation des valeurs de sortie
      for(unsigned i = 0; i<v_output_tampon.size(); i++){
        m_output[v_output_tampon.at(i)->getName()].at(it_delta_cycle) = v_output_tampon.at(i)->getValueAndReset();
      }
      cout << "sortie recupere " << endl;
      it_delta_cycle++;
      //Mise à jour des nouvelle valeur d'entrée
      cout << "nouvelle update " << endl;
      if(it_delta_cycle < v_duree_delta.size()){
        for(unsigned i = 0; i<v_input.size(); i++){
          for(unsigned j = 0; j<m_input[v_input.at(i)].size(); j++){
            m_input[v_input.at(i)].at(j)->update_input(m_stimulis[v_input.at(i)].at(it_delta_cycle));
          }
        }
      }
      cout << "fin update " << endl << endl;
    }

    //Simu des portes à faire.
    for(unsigned i = 0; i<v_gate_all.size();i++){
      v_gate_all.at(i)->calc_and_affect();
    }

  }

  //Appel du parser de sortie

}
