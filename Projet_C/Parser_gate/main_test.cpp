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

using namespace std;

int main(int argc, char const *argv[]) {

  /////////////////////////////////////////////////////////////////////////////
  //Déclaration des structure de données général
  /////////////////////////////////////////////////////////////////////////////

  vector<Gate*> v_gate;
  vector<string> v_int;
  vector<string> v_out;
  map<string, Gate*> v_tamp_output;
  map<string, list<Gate*> > m_input;
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

  //Appel du parser de lecture du fichier .dot
  //Et detection d'erreur de sortie
  /////////////////////////////////////////////////////////////////////////////
  //Appel du parser du .dot
  /////////////////////////////////////////////////////////////////////////////

  if(parser_gate(&m_input,&m_output,&v_gate,&v_tamp_output,&v_int,&v_out,path_stru)!=0){
    cout<<"Erreur de lecture du fichier .dot"<< endl;
    exit(EXIT_FAILURE);
  }

  /////////////////////////////////////////////////////////////////////////////
  //Controle vetor gate
  /////////////////////////////////////////////////////////////////////////////

  // for(int i = 0; i<v_gate.size();i++){
  //   cout << v_gate.at(i)->getName()<<endl;
  // }

  /////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME + DELETE
  /////////////////////////////////////////////////////////////////////////////

  for(int i = 0; i<v_gate.size();i++){
    delete v_gate.at(i);
  }

  cout << "FIN PRG"<<endl;
}
