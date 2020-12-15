#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

//include des Parser
#include "./Parser_gate/Parser_gate.h"
#include "./Parser_stimuli/Parser_stimuli.h"

//include des gate
#include "./Porte/Gate.h"

#include "./Porte/Gate_comb.h"
#include "./Porte/Combinatoire/And.h"
#include "./Porte/Combinatoire/Inv.h"
#include "./Porte/Combinatoire/Or.h"
#include "./Porte/Combinatoire/Nand.h"
#include "./Porte/Combinatoire/Nor.h"
#include "./Porte/Combinatoire/Xor.h"
#include "./Porte/Combinatoire/Xnor.h"

#include "./Porte/Gate_out.h"

//#include "../Porte/Gate_mux.h"

int main(){
  map<string,vector<Gate *>* > m_input; //map des entres du circuit
  map<string,vector<int>* > m_output; //map des sorties du circuit
  vector<Gate *> v_output_tampon; //map des gate tampon de sortie
  vector<Gate *> v_gate_all; //vector des gates du ciruit
  vector<string> v_input; //vector des clé entrés
  vector<string> v_output; //vector des clé sorties

  map<string,vector<int>* > m_stimulis; //map des différents stimuls clé = entrée vector = valeur
  vector<int> v_duree_delta; //vector de la duréee de chaque stimulis

  //Appel du parser gate
  char path_stru[] = "test1.dot";
  if (parser_gate(&m_input, &m_output, &v_gate_all, &v_output_tampon, &v_input, &v_output, path_stru)){
    return 1;
  }

  //Appel du parser simu
  char path_stimuli[] = "test1_stimulis.json";
  if (parser_stimuli(&v_input, &v_duree_delta, &m_stimulis, path_stimuli)){
    return 1;
  }

  for(unsigned i = 0; i < v_output.size(); i++){
    for(unsigned j = 0; j < v_duree_delta.size(); j++){
      m_output[v_output.at(i)]->push_back(0);
    }
  }

  //Simulation
  //Premiere update des entree
  unsigned it_delta_cycle = 0; //indice du delta_cycle
  for(unsigned i = 0; i<v_input.size(); i++){ //on parcourt la liste v_input pour recuper les clés d'input
    for(unsigned j = 0; j<m_input[v_input.at(i)]->size(); j++){ //on parcourt le vecteur correspondant à la clé
       m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle)); //on update chaque gate avec la nouvelle valeur de stimulis
       cout << endl <<endl;
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

    if(stab){
      //Recuperation des valeurs de sortie
      for(unsigned i = 0; i<v_output_tampon.size(); i++){
        m_output[v_output_tampon.at(i)->getName()]->at(it_delta_cycle) = v_output_tampon.at(i)->getValueAndReset();
      }
      it_delta_cycle++;
      //Mise à jour des nouvelle valeur d'entrée
      if(it_delta_cycle < v_duree_delta.size()){
        for(unsigned i = 0; i<v_input.size(); i++){
          for(unsigned j = 0; j<m_input[v_input.at(i)]->size(); j++){
            m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle));
          }
        }
      }
    }

    //Simu des portes à faire.
    for(unsigned i = 0; i<v_gate_all.size();i++){
      v_gate_all.at(i)->calc_and_affect();
    }
  }

  //Appel du parser de sortie


  for (unsigned i = 0; i < v_output.size();i++){
    cout << v_output.at(i) << endl;
    for(unsigned j = 0; j<m_output[v_output.at(i)]->size();j++){
      cout << m_output[v_output.at(i)]->at(j) << endl;
    }
  }

  //Liberation de la memoire
  for(map<string, vector<Gate*>*>::iterator itr = m_input.begin(); itr != m_input.end(); itr++){
    cout << "Destruction de l'entrée  " << itr->first << endl;
    delete itr->second;
  }

  for(map<string, vector<int>* >::iterator itr = m_output.begin(); itr != m_output.end(); itr++){
    cout << "Destruction de la sortie  " << itr->first <<endl;
    delete itr->second;
  }

  for(int i = 0;i<v_input.size();i++){
    cout << "Destruction du stimuli d'entrée "<<v_input.at(i)<<endl;
    delete m_stimulis.at(v_input.at(i));
  }

}
