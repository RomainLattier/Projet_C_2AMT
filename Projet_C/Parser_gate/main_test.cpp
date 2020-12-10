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
  map<string, list<Gate*> > m_input;
  map<string, vector<int> > m_output;

  //Appel du parser de lecture du fichier .dot
  //Et detection d'erreur de sortie

  /////////////////////////////////////////////////////////////////////////////
  //Appel du parser du .dot
  /////////////////////////////////////////////////////////////////////////////

  if(parser_gate(&m_input,&m_output,&v_gate)!=0){
    cout<<"Erreur de lecture du fichier .dot"<< endl;
    exit(EXIT_FAILURE);
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  /////////////////////////////////////////////////////////////////////////////

  //cout << "FIN PRG"<<endl;
}
