#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <cstdlib>


#include "Parser_gate.h"
#include "../Porte/Combinatoire/And.h"

using namespace std;

int main(int argc, char const *argv[]) {

  /////////////////////////////////////////////////////////////////////////////
  //Déclaration des structure de données général
  /////////////////////////////////////////////////////////////////////////////

  vector<Gate*> v_gate;
  vector<Gate*> v_tamp_output;
  map<string, list<Gate*> > m_input;
  map<string, vector<int> > m_output;

  //Appel du parser de lecture du fichier .dot
  //Et detection d'erreur de sortie

  /////////////////////////////////////////////////////////////////////////////
  //Appel du parser du .dot
  /////////////////////////////////////////////////////////////////////////////

  if(parser_gate(&m_input,&m_output,&v_gate,&v_tamp_output)!=0){
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
