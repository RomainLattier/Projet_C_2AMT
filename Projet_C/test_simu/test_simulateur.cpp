#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

//include des Parser
#include "../Parser_gate/Parser_gate.h"
#include "../Parser_stimuli/Parser_stimuli.h"

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

  //Variable de test
  // v_input.push_back("A");
  // v_input.push_back("B");
  // v_input.push_back("C");
  // v_input.push_back("D");
  //
  // v_output.push_back("S");
  // v_output.push_back("Q");
  //
  // Xor X1("Xor1_2", 2);
  // And A1("And1_3", 3);
  // Or O1("Or1_2", 2);
  // Gate_out S("S", 1);
  // Gate_out Q("Q", 1);
  //
  // X1.add_input(0);
  // X1.add_input(0);
  //
  // A1.add_input(0);
  // A1.add_input(0);
  // A1.add_input(0);
  //
  // O1.add_input(0);
  // O1.add_input(0);
  //
  // S.add_input(0);
  //
  // Q.add_input(0);
  //
  // X1.add_output(&S);
  // X1.add_output(&O1);
  //
  // A1.add_output(&O1);
  //
  // O1.add_output(&Q);
  //
  // v_output_tampon.push_back(&S);
  // v_output_tampon.push_back(&Q);
  // v_gate_all.push_back(&A1);
  // v_gate_all.push_back(&O1);
  // v_gate_all.push_back(&X1);
  //
  //
  // vector<Gate *>* v_a = new vector<Gate *>();
  // v_a->push_back(&X1);
  // m_input.insert(pair<string,vector<Gate *>* >("A",v_a) );
  //
  // vector<Gate *>* v_b = new vector<Gate *>();
  // v_b->push_back(&X1);
  // v_b->push_back(&A1);
  // m_input.insert(pair<string,vector<Gate *>* >("B",v_b) );
  //
  // vector<Gate *>* v_c = new vector<Gate *>();
  // v_c->push_back(&A1);
  // m_input.insert(pair<string,vector<Gate *>* >("C",v_c) );
  //
  // vector<Gate *>* v_d = new vector<Gate *>();
  // v_d->push_back(&A1);
  // m_input.insert(pair<string,vector<Gate *>* >("D",v_d) );
  //
  // vector<int>* v_s = new vector<int>();
  // v_s->push_back(0);
  // v_s->push_back(7);
  // v_s->push_back(0);
  // v_s->push_back(0);
  // v_s->push_back(0);
  // v_s->push_back(7);
  // v_s->push_back(0);
  // v_s->push_back(0);
  // v_s->push_back(0);
  // v_s->push_back(7);
  // v_s->push_back(0);
  // v_s->push_back(0);
  // v_s->push_back(0);
  // v_s->push_back(7);
  // v_s->push_back(0);
  // v_s->push_back(0);
  //
  // vector<int>* v_q = new vector<int>();
  // v_q->push_back(0);
  // v_q->push_back(7);
  // v_q->push_back(0);
  // v_q->push_back(0);
  // v_q->push_back(0);
  // v_q->push_back(7);
  // v_q->push_back(0);
  // v_q->push_back(0);
  // v_q->push_back(0);
  // v_q->push_back(7);
  // v_q->push_back(0);
  // v_q->push_back(0);
  // v_q->push_back(0);
  // v_q->push_back(7);
  // v_q->push_back(0);
  // v_q->push_back(0);
  //
  // m_output.insert(pair<string,vector<int>* >("S",v_s) );
  // m_output.insert(pair<string,vector<int>* >("Q",v_q) );
  //
  // vector<int>* v_stimulisA = new vector<int>();
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(0);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  // v_stimulisA->push_back(1);
  //
  // m_stimulis.insert(pair<string,vector<int>* >("A",v_stimulisA) );
  //
  // vector<int>* v_stimulisB = new vector<int>();
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(0);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(1);
  // v_stimulisB->push_back(1);
  //
  // m_stimulis.insert(pair<string,vector<int>* >("B",v_stimulisB) );
  //
  // vector<int>* v_stimulisC =new vector<int>();
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(0);
  // v_stimulisC->push_back(1);
  // v_stimulisC->push_back(1);
  //
  // m_stimulis.insert(pair<string,vector<int>* >("C",v_stimulisC) );
  //
  // vector<int>* v_stimulisD = new vector<int>();
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  // v_stimulisD->push_back(0);
  // v_stimulisD->push_back(1);
  //
  // m_stimulis.insert(pair<string,vector<int>* >("D",v_stimulisD) );
  //
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);
  // v_duree_delta.push_back(2);

  cout << v_output.size() << endl;

  for (unsigned i = 0; i < v_output.size();i++){
    cout << v_output.at(i) << endl;
    for(unsigned j = 0; j<m_output[v_output.at(i)]->size();j++){
      cout << m_output[v_output.at(i)]->at(j) << endl;
    }
  }

  //Simulation
  //Premiere update des entree
  cout << "avant 1er update" << endl;
  unsigned it_delta_cycle = 0; //indice du delta_cycle
  for(unsigned i = 0; i<v_input.size(); i++){ //on parcourt la liste v_input pour recuper les clés d'input
    for(unsigned j = 0; j<m_input[v_input.at(i)]->size(); j++){ //on parcourt le vecteur correspondant à la clé
       // cout << "i " << i << endl;
       // cout << "j " << j << endl;
       // cout << v_input.at(i) << endl;
       // cout << m_input[v_input.at(i)].at(j)->getName() << endl;
       // cout << it_delta_cycle << endl;
       // cout << "size stimulis " << m_stimulis[v_input.at(i)].size() << endl;
       // cout << "valeur stimulis" << m_stimulis[v_input.at(i)].at(it_delta_cycle) << endl;
       m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle)); //on update chaque gate avec la nouvelle valeur de stimulis
       cout << endl <<endl;
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
        // cout << "i " << i << endl;
        // cout << "valeur en sortie " << S.getValueOutput() << endl;
        // cout << "v_output_tampon.at(i)->getName() " << v_output_tampon.at(i)->getName() << endl;
        m_output[v_output_tampon.at(i)->getName()]->at(it_delta_cycle) = v_output_tampon.at(i)->getValueAndReset();
      }
      cout << "sortie recupere " << endl;
      it_delta_cycle++;
      //Mise à jour des nouvelle valeur d'entrée
      cout << "nouvelle update " << endl;
      if(it_delta_cycle < v_duree_delta.size()){
        for(unsigned i = 0; i<v_input.size(); i++){
          for(unsigned j = 0; j<m_input[v_input.at(i)]->size(); j++){
            // cout << "i " << i << endl;
            // cout << "j " << j << endl;
            // cout << v_input.at(i) << endl;
            // cout << m_input[v_input.at(i)].at(j)->getName() << endl;
            // cout << "it_delta_cycle " << it_delta_cycle << endl;
            // cout << "valeur stimulis" << m_stimulis[v_input.at(i)].at(it_delta_cycle) << endl;
            m_input[v_input.at(i)]->at(j)->update_input(m_stimulis[v_input.at(i)]->at(it_delta_cycle));
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
