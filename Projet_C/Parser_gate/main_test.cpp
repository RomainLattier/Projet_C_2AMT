#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <cstdlib>


#include "Parser_gate.cpp"
#include "Gate.h" // A MODIFIER avec le bon nom de la classe

using namespace std;


int main(int argc, char const *argv[]) {

  list<string> l_NameGate;
  map<string, Gate*> m_input;
  map<string, vector<bool> *> m_output;

//Appel du parser de lecture du fichier .dot
//Et detection d'erreur de sortie

if(parser_gate(&m_input,&m_output,&l_NameGate)!=0){
  cout<<"Erreur de lecture du fichier .dot"<< endl;
  exit(EXIT_FAILURE);
}


cout << "FIN PRG"<<endl;
}
