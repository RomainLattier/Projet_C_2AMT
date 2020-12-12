#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <stdlib.h>

#include "Parser_gate.h"
#include "../Porte/Combinatoire/And.h"
#include "../Porte/Combinatoire/Inv.h"
#include "../Porte/Combinatoire/Nand.h"
#include "../Porte/Combinatoire/Nor.h"
#include "../Porte/Combinatoire/Or.h"
#include "../Porte/Combinatoire/Xnor.h"
#include "../Porte/Combinatoire/Xor.h"
#include "../Porte/Gate_out.h"

using namespace std;

int main(int argc, char const *argv[]) {

  /////////////////////////////////////////////////////////////////////////////
  //Déclaration des structure de données général
  /////////////////////////////////////////////////////////////////////////////

  vector<Gate*> v_gate;
  vector<string> v_int;
  vector<string> v_out;
  map<string, Gate*> m_tamp_output;
  map<string, vector<Gate*>* > m_input;
  map<string, vector<int>* > m_output;

  char path_stru[] = "Test_lecture.dot";
  // char path_stru[];
  // char path_stimu[];

  /////////////////////////////////////////////////////////////////////////////
  //Demande des path des deux fichiers
  /////////////////////////////////////////////////////////////////////////////
  // cout <<" Donnez le chemin du fichier structure du circuit (fichier .dot)"<<endl;
  // cin >> path_stru;
  // cout <<" Donnez le chemin du fichier stimulis en entrée du circuit (fichier wavedrom)"<<endl;
  // cin >> path_stimu;


  /////////////////////////////////////////////////////////////////////////////
  //Appel du parser du .dot
  /////////////////////////////////////////////////////////////////////////////

  if(parser_gate(&m_input,&m_output,&v_gate,&m_tamp_output,&v_int,&v_out,path_stru)!=0){
    cout<<"Erreur de lecture du fichier .dot"<< endl;
    exit(EXIT_FAILURE);
  }

  /////////////////////////////////////////////////////////////////////////////
  //Controle vetor gate
  /////////////////////////////////////////////////////////////////////////////

  // for(int i = 0; i<v_gate.size();i++){
  //   cout << v_gate.at(i)->getName()<<endl;
  // }

  // for(int i = 0; i<v_gate.size();i++){
  //   v_gate.at(i)->print_output_name();
  // }



  /////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME + DELETE des dynamiques
  /////////////////////////////////////////////////////////////////////////////

  for(int i = 0; i<v_gate.size();i++){
    delete v_gate.at(i);
  }

  for(map<string, Gate*>::iterator itr = m_tamp_output.begin(); itr != m_tamp_output.end(); itr++){
    delete itr->second;
  }

  for(map<string, vector<Gate*>*>::iterator itr = m_input.begin(); itr != m_input.end(); itr++){
    cout << "Destruction de l'entrée  " << itr->first << endl;
    delete itr->second;
  }

  for(map<string, vector<int>* >::iterator itr = m_output.begin(); itr != m_output.end(); itr++){
    cout << "Destruction de la sortie  " << itr->first <<endl;
    delete itr->second;
  }

  cout << "FIN PRG"<<endl;
}
