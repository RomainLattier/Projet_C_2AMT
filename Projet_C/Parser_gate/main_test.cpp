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
  vector<string> v_in;
  vector<string> v_out;
  vector<Gate*> v_tamp_output;
  map<string, vector<Gate*>* > m_input;
  map<string, vector<int>* > m_output;

  /////////////////////////////////////////////////////////////////////////////
  //Demande des path des deux fichiers
  /////////////////////////////////////////////////////////////////////////////

  char path_stru[] = "Test_lecture.dot";
  // char path_stru[];
  // char path_stimu[];
  // cout <<" Donnez le chemin du fichier structure du circuit (fichier .dot)"<<endl;
  // cin >> path_stru;
  // cout <<" Donnez le chemin du fichier stimulis en entrée du circuit (fichier wavedrom)"<<endl;
  // cin >> path_stimu;

  /////////////////////////////////////////////////////////////////////////////
  //Appel du parser du .dot
  /////////////////////////////////////////////////////////////////////////////

  if(parser_gate(&m_input,&m_output,&v_gate,&v_tamp_output,&v_in,&v_out,path_stru)!=0){
    cout<<"Erreur de lecture du fichier .dot"<< endl;
    exit(EXIT_FAILURE);
  }

  /////////////////////////////////////////////////////////////////////////////
  //Controle TEST
  /////////////////////////////////////////////////////////////////////////////

  //test création des portes
  cout<<"\n------------------------------------"<<endl;
  cout << "Test de la création des portes et du vector de gate"<<endl;
  for(int i = 0; i<v_gate.size();i++){
    cout <<"\nLa porte "<< v_gate.at(i)->getName()<< " a pour sorties :"<<endl;
    v_gate.at(i)->print_output_name();
    cout << "et a "<<v_gate.at(i)->get_nb_of_entry()<<" entrées"<<endl;
  }

  //test vecteur in
  cout<<"\n------------------------------------"<<endl;
  cout <<"Test du vecteur input"<<endl;
  for(int i = 0; i<v_in.size();i++){
    cout << v_in.at(i)<<endl;
  }

  //test vector out
  cout<<"\n------------------------------------"<<endl;
  cout <<"Test du vecteur output"<<endl;
  for(int i = 0; i<v_out.size();i++){
    cout << v_out.at(i)<<endl;
  }

  //test creation map INPUT
  cout<<"\n------------------------------------"<<endl;
  cout <<"Test de la création de la map input"<<endl;
  for(int i = 0;i<v_in.size();i++){
    cout << "\nL'entrée " << v_in.at(i)<< " est relié à la porte "<<endl;
    for(int j = 0; j<m_input.at(v_in.at(i))->size();j++){
      cout << m_input.at(v_in.at(i))->at(j)->getName()<<endl;
    }
  }

  //test creation map output
  cout<<"\n------------------------------------"<<endl;
  cout <<"Test de la création de la map input"<<endl;
  for(int i = 0;i<v_out.size();i++){
    cout << "\nLa sortie " << v_out.at(i)<< " a un vecteur avec les valeurs :"<<endl;
    for(int j = 0; j<m_output.at(v_out.at(i))->size();j++){
      cout << m_input.at(v_out.at(i))->at(j)<<endl;
    }
  }

  //test creation vector tamp output
  cout<<"\n------------------------------------"<<endl;
  cout <<"Test de la création de la map tamp output"<<endl;
  for(int i = 0;i<v_tamp_output.size();i++){
    cout << "\nLa porte tampon " << v_tamp_output.at(i)->getName()<< " a "<<
    v_tamp_output.at(i)->get_nb_of_entry()<<" entrée"<<endl;
  }

  /////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME + DELETE des dynamiques
  /////////////////////////////////////////////////////////////////////////////

  for(int i = 0; i<v_gate.size();i++){
    delete v_gate.at(i);
  }

  for(int i = 0; i<v_tamp_output.size();i++){
    delete v_tamp_output.at(i);
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
