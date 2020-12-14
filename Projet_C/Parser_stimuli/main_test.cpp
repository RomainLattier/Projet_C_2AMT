#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <stdlib.h>

#include "Parser_stimuli.h"


using namespace std;

int main(int argc, char const *argv[]) {

  /////////////////////////////////////////////////////////////////////////////
  //Déclaration des structure de données général
  /////////////////////////////////////////////////////////////////////////////

  vector<string> v_in;
  vector<int> v_delta;
  map<string, vector<int>* > m_stimuli;

  v_in.push_back("A"); // A enlever
  v_in.push_back("B");
//  v_in.push_back("C_in");

  char path_stimuli[] = "Test_delta_cycle.json";

  //Appel du parser de lecture du fichier .dot
  //Et detection d'erreur de sortie
  /////////////////////////////////////////////////////////////////////////////
  //Appel du parser du .dot
  /////////////////////////////////////////////////////////////////////////////

  if(parser_stimuli(&v_in,&v_delta,&m_stimuli,path_stimuli)!=0){
    cout<<"Erreur de lecture du fichier wavedrom"<< endl;
    exit(EXIT_FAILURE);
  }

  /////////////////////////////////////////////////////////////////////////////
  //Controle
  /////////////////////////////////////////////////////////////////////////////

  //Controle vector des durée de delta cycle

  cout<<"v_delta :"<<endl;
  for(int i = 0;i<v_delta.size();i++){
    cout<<v_delta.at(i)<<endl;
  }

  //Test map stimuli
  cout <<"\nTest de la création de la map input"<<endl;
  for(int i = 0;i<v_in.size();i++){
    cout << "\nLa sortie " << v_in.at(i)<< " a un vecteur avec les valeurs :"<<endl;
    for(int j = 0; j<m_stimuli.at(v_in.at(i))->size();j++){
      cout << m_stimuli.at(v_in.at(i))->at(j)<<endl;
    }
  }



  /////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME + DELETE
  /////////////////////////////////////////////////////////////////////////////


  cout << "FIN PRG"<<endl;
}
