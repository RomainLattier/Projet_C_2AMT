#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

//include des Parser
//#include "/Parser_gate/Parser_gate.h"

//include des gate
#include "../Porte/Gate.h"

#include "../Porte/Gate_comb.h"
#include "../Porte/Combinatoire/And.h"
/*#include "/Porte/Combinatoire/Inv.h"
#include "/Porte/Combinatoire/Or.h"
#include "/Porte/Combinatoire/Nand.h"
#include "/Porte/Combinatoire/Nor.h"
#include "/Porte/Combinatoire/Xor.h"
#include "/Porte/Combinatoire/Xnor.h"*/

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


  //Variable de test
  v_input.push_back("A");
  v_input.push_back("B");

  v_output.push_back("S");

  And A1("And_1_2", 2);
  Gate_out S("S",1);

  A1.add_input(0);
  A1.add_input(0);

  A1.add_output(&S);

  S.add_input(0);

  v_output_tampon.push_back(&S);
  v_gate_all.push_back(&A1);

  vector<Gate*> v_g;
  v_g.push_back(&A1);

  m_input.insert(pair<string,vector<Gate *> >("A",v_g) );
  m_input.insert(pair<string,vector<Gate *> >("B",v_g) );

  vector<int> v_o;
  v_o.push_back(0);
  v_o.push_back(7);
  v_o.push_back(0);
  v_o.push_back(0);

  m_output.insert(pair<string,vector<int> >("S",v_o) );

  vector<int> v_stimulisA;
  v_stimulisA.push_back(0);
  v_stimulisA.push_back(0);
  v_stimulisA.push_back(1);
  v_stimulisA.push_back(1);

  m_stimulis.insert(pair<string,vector<int> >("A",v_stimulisA) );

  vector<int> v_stimulisB;
  v_stimulisB.push_back(0);
  v_stimulisB.push_back(1);
  v_stimulisB.push_back(0);
  v_stimulisB.push_back(1);

  m_stimulis.insert(pair<string,vector<int> >("B",v_stimulisB) );

  v_duree_delta.push_back(2);
  v_duree_delta.push_back(2);
  v_duree_delta.push_back(2);
  v_duree_delta.push_back(2);

  for (unsigned i = 0; i < v_output.size();i++){
    cout << v_output.at(i) << endl;
    for(unsigned j = 0; j<m_output[v_output.at(i)].size();j++){
      cout << m_output[v_output.at(i)].at(j) << endl;
    }
  }

  //Simulation
  //Premiere update des entree
  cout << "avant 1er update" << endl;
  unsigned it_delta_cycle = 0; //indice du delta_cycle
  for(unsigned i = 0; i<v_input.size(); i++){ //on parcourt la liste v_input pour recuper les clés d'input
    for(unsigned j = 0; j<m_input[v_input.at(i)].size(); j++){ //on parcourt le vecteur correspondant à la clé
      // cout << "i " << i << endl;
      // cout << "j " << j << endl;
      // cout << v_input.at(i) << endl;
      // cout << m_input[v_input.at(i)].at(j)->getName() << endl;
      // cout << "valeur stimulis" << m_stimulis[v_input.at(i)].at(it_delta_cycle) << endl;
      m_input[v_input.at(i)].at(j)->update_input(m_stimulis[v_input.at(i)].at(it_delta_cycle)); //on update chaque gate avec la nouvelle valeur de stimulis
    }
  }
  cout << "apres 1er update" << endl;

  //Boucle de simu

  while (it_delta_cycle < v_duree_delta.size()) {
    int stab = 1;
    // cout << "v_output_tampon.size()" << v_output_tampon.size() <<endl;
    for(unsigned i = 0; i<v_output_tampon.size(); i++){ //recherche si la simu pour ce delta est fini
      // cout << "i " << i << endl;
      // cout << "stab " << stab << endl;
      // cout << "(i<v_output_tampon.size()) " << (i<v_output_tampon.size()) << endl;
      // cout << "!v_output_tampon.at(i)->is_stable() " << (!v_output_tampon.at(i)->is_stable()) << endl;
      if(!v_output_tampon.at(i)->is_stable()){
        // cout << "dans le if" << endl;
        stab = 0;
      }
    }

    cout << "stab apres check update " << stab <<endl;
    cout << "it_delta_cycle " << it_delta_cycle << endl;
    if(stab){
      cout << "recup des sorties" << endl;
      // cout << "v_output_tampon.size() " << v_output_tampon.size() << endl;
      //Recuperation des valeurs de sortie
      for(unsigned i = 0; i<v_output_tampon.size(); i++){
        // cout << "i " << i << endl << endl;
        // cout << "valeur en sortie " << S.getValueOutput() << endl << endl;
        // cout << "v_output_tampon.at(i)->getName() " << v_output_tampon.at(i)->getName() << endl;
        m_output[v_output_tampon.at(i)->getName()].at(it_delta_cycle) = v_output_tampon.at(i)->getValueAndReset();
      }
      cout << "sortie recupere " << endl;
      it_delta_cycle++;
      //Mise à jour des nouvelle valeur d'entrée
      cout << "nouvelle update " << endl;
      if(it_delta_cycle < v_duree_delta.size()){
        for(unsigned i = 0; i<v_input.size(); i++){
          for(unsigned j = 0; j<m_input[v_input.at(i)].size(); j++){
            // cout << "i " << i << endl;
            // cout << "j " << j << endl;
            // cout << v_input.at(i) << endl;
            // cout << m_input[v_input.at(i)].at(j)->getName() << endl;
            // cout << "it_delta_cycle " << it_delta_cycle << endl;
            // cout << "valeur stimulis" << m_stimulis[v_input.at(i)].at(it_delta_cycle) << endl;
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


  for (unsigned i = 0; i < v_output.size();i++){
    cout << v_output.at(i) << endl;
    for(unsigned j = 0; j<m_output[v_output.at(i)].size();j++){
      cout << m_output[v_output.at(i)].at(j) << endl;
    }
  }
}
