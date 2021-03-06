#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <math.h>

//include des Parser
#include "../Parser_gate/Parser_gate.h"
#include "../Parser_stimuli/Parser_stimuli.h"
#include "../wavedrom_sorti/wavedrom.h"

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

#include "../Porte/Gate_mux.h"

int main(){
  map<string,vector<Gate *>* > m_input; //map des entres du circuit
  map<string,vector<int>* > m_output; //map des sorties du circuit
  vector<Gate *> v_output_tampon; //map des gate tampon de sortie
  vector<Gate *> v_gate_all; //vector des gates du ciruit
  vector<string> v_input; //vector des clé entrés
  vector<string> v_output; //vector des clé sorties

  map<string,vector<int>* > m_stimulis; //map des différents stimuls clé = entrée vector = valeur
  vector<int> v_duree_delta; //vector de la duréee de chaque stimulis

  // string path_stru = "../Examen/circuits/full_adder.dot";
  // string path_stimuli = "../Examen/stimuli/full_adder.json";
  // string path_file_out = "./test_exam/full_adder_result.json";

  string path_stru ;
  string path_stimuli ;
  string path_file_out;
  cout <<" Donnez le chemin du fichier structure du circuit (fichier .dot)"<<endl;
  cin >> path_stru;
  cout <<" Donnez le chemin du fichier stimulis en entrée du circuit (fichier wavedrom avec extansion .json)"<<endl;
  cin >> path_stimuli;
  cout <<" Donnez le chemin avec le nom du fichier stimulis de sortie (fichier wavedrom avec extansion .json)"<<endl;
  cin >> path_file_out;

  //Appel du parser gate
  if (parser_gate(&m_input, &m_output, &v_gate_all, &v_output_tampon, &v_input, &v_output,&path_stru)){
    cout << "\nErreur de la lecture du fichier structure du circuit."<<endl;
    return 1;
  }

  //Appel du parser simu
  if (parser_stimuli(&v_input, &v_duree_delta, &m_stimulis,&path_stimuli)){
    cout << "\nErreur de la lecture du fichier stimulis du circuit."<<endl;
    return 1;
  }

  for(unsigned i = 0; i < v_output.size(); i++){
    for(unsigned j = 0; j < v_duree_delta.size(); j++){
      m_output[v_output.at(i)]->push_back(0);
    }
  }

  for(unsigned i = 0; i < v_gate_all.size(); i++){
    if(v_gate_all.at(i)->get_output_size() == 0){
      cout << "\nLa porte " << v_gate_all.at(i)->getName() << " n'a pas de sortie défini" << endl;
      return 1;
    }
  }

  for(unsigned i = 0; i<v_gate_all.size(); i++){
    if(v_gate_all.at(i)->get_input_size() != v_gate_all.at(i)->get_nb_of_entry()){
      cout << "\nLa porte " << v_gate_all.at(i)->getName() << " n'a pas nb_of_entry = input size" << endl;
      return 1;
    }
  }

  cout<<"\n------------------------------------"<<endl;
  cout << "Test de la création des portes et du vector de gate"<<endl;
  for(int i = 0; i<v_gate_all.size();i++){
    cout <<"\nLa porte "<< v_gate_all.at(i)->getName()<< " a pour sorties :"<<endl;
    v_gate_all.at(i)->print_output_name();
    cout << "et a "<<v_gate_all.at(i)->get_nb_of_entry()<<" entrées"<<endl;
  }

  //test creation map INPUT
  cout<<"\n------------------------------------"<<endl;
  cout <<"Test de la création de la map input"<<endl;
  for(int i = 0;i<v_input.size();i++){
    cout << "\nL'entrée " << v_input.at(i)<< " est relié à la porte "<<endl;
    for(int j = 0; j<m_input.at(v_input.at(i))->size();j++){
      cout << m_input.at(v_input.at(i))->at(j)->getName()<<endl;
    }
  }

  // for (unsigned i = 0; i < v_output.size();i++){
  //   cout << v_output.at(i) << endl;
  //   for(unsigned j = 0; j<m_output[v_output.at(i)]->size();j++){
  //     cout << m_output[v_output.at(i)]->at(j) << endl;
  //   }
  // }

  //Simulation
  //Premiere update des entree
  cout << "\navant 1er update" << endl;
  unsigned it_delta_cycle = 0; //indice du delta_cycle
  for(unsigned i = 0; i<v_input.size(); i++){ //on parcourt la liste v_input pour recuper les clés d'input
    for(unsigned j = 0; j<m_input[v_input.at(i)]->size(); j++){ //on parcourt le vecteur correspondant à la clé
       // cout << "i " << i << endl;
       // cout << "j " << j << endl;
       // cout << v_input.at(i) << endl;
       // cout << m_input[v_input.at(i)]->at(j)->getName() << endl;
       // cout << it_delta_cycle << endl;
       // cout << "size stimulis " << m_stimulis[v_input.at(i)]->size() << endl;
       // cout << "valeur stimulis " << m_stimulis[v_input.at(i)]->at(it_delta_cycle) << endl;
       // cout << "m_input[v_input.at(i)]->at(j)->get_is_a_mux() " << m_input[v_input.at(i)]->at(j)->get_is_a_mux() << endl;
       if(m_input[v_input.at(i)]->at(j)->get_is_a_mux()){
         m_input[v_input.at(i)]->at(j)->update_mux(m_stimulis[v_input.at(i)]->at(it_delta_cycle), v_input.at(i));
         // cout << "valeur ajouté dans mux " <<  m_stimulis[v_input.at(i)]->at(it_delta_cycle) << " dans " << v_input.at(i) << endl;
       }
       else{
         // cout << "m_stimulis[v_input.at(i)]->at(it_delta_cycle) " << m_stimulis[v_input.at(i)]->at(it_delta_cycle) << endl;
         // cout << "m_input[v_input.at(i)]->at(j)->get_input_size() " << m_input[v_input.at(i)]->at(j)->get_input_size() << endl;
         m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle)); //on update chaque gate avec la nouvelle valeur de stimulis
       }
    }
  }
  cout << "\napres 1er update" << endl;

  //Boucle de simu

  // int debug = 0;
  cout << endl << "\ndebut boucle simu" << endl;

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

    // cout << "stab apres check update " << stab <<endl;
    // cout << "it_delta_cycle " << it_delta_cycle << endl;
    if(stab){
      // cout << "\nrecup des sorties" << endl;
      // cout << "v_output_tampon.size() " << v_output_tampon.size() << endl;
      //Recuperation des valeurs de sortie
      for(unsigned i = 0; i<v_output_tampon.size(); i++){
        // cout << "i " << i << endl;
        // cout << "valeur en sortie " << S.getValueOutput() << endl;
        // cout << "v_output_tampon.at(i)->getName() " << v_output_tampon.at(i)->getName() << endl;
        m_output[v_output_tampon.at(i)->getName()]->at(it_delta_cycle) = v_output_tampon.at(i)->getValueAndReset();
      }
      // cout << "\nsortie recupere " << endl;
      it_delta_cycle++;
      //Mise à jour des nouvelle valeur d'entrée
      // cout << "\nnouvelle update " << endl;
      if(it_delta_cycle < v_duree_delta.size()){
        for(unsigned i = 0; i<v_input.size(); i++){
          for(unsigned j = 0; j<m_input[v_input.at(i)]->size(); j++){
            // cout << "i " << i << endl;
            // cout << "j " << j << endl;
            // cout << v_input.at(i) << endl;
            // cout << m_input[v_input.at(i)].at(j)->getName() << endl;
            // cout << "it_delta_cycle " << it_delta_cycle << endl;
            // cout << "valeur stimulis" << m_stimulis[v_input.at(i)].at(it_delta_cycle) << endl;
            if(m_input[v_input.at(i)]->at(j)->get_is_a_mux()){
              m_input[v_input.at(i)]->at(j)->update_mux(m_stimulis[v_input.at(i)]->at(it_delta_cycle), v_input.at(i));
            }
            else{
              m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle)); //on update chaque gate avec la nouvelle valeur de stimulis
            }
            // m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle));
          }
        }
      }
      // cout << "\nfin update " << endl << endl;
    }

    //Simu des portes à faire.
    for(unsigned i = 0; i<v_gate_all.size();i++){
      if(v_gate_all.at(i)->calc_and_affect()){
        return 1;
      }
    }

    // if(debug == 3){
    //   return 0;
    // }
    // debug ++;

  }

  cout <<"Fin boucle de simu " << endl;

  //Appel du parser de sortie


  // for (unsigned i = 0; i < v_output.size();i++){
  //   cout << v_output.at(i) << endl;
  //   for(unsigned j = 0; j<m_output[v_output.at(i)]->size();j++){
  //     cout << m_output[v_output.at(i)]->at(j) << endl;
  //   }
  // }

  if (wavedrom_output(&v_input,&v_output,&v_duree_delta,&m_stimulis,&m_output,&path_file_out)){
    cout <<"\nErreur de l'écriture du fichier de sortie."<<endl;
    return 1;
  }

  //Liberation de la memoire
  for(map<string, vector<Gate*>*>::iterator itr = m_input.begin(); itr != m_input.end(); itr++){
//    cout << "Destruction de l'entrée  " << itr->first << endl;
    delete itr->second;
  }

  for(map<string, vector<int>* >::iterator itr = m_output.begin(); itr != m_output.end(); itr++){
//    cout << "Destruction de la sortie  " << itr->first <<endl;
    delete itr->second;
  }

  for(int i = 0;i<v_input.size();i++){
//    cout << "Destruction du stimuli d'entrée "<<v_input.at(i)<<endl;
    delete m_stimulis.at(v_input.at(i));
  }

}
