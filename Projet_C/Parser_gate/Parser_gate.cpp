#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "Gate.h"

using namespace std;

int parser_gate(map<string,list<Gate *> > *m_input,map<string,vector<bool> > *m_output,list<Gate *> *l_gate, vector<string> *v_gate_avaible) {

  ////////////////////////////////////////////////////////////////////////////////
  //VARIABLES
  ////////////////////////////////////////////////////////////////////////////////

  string ligne; //lecture ligne par ligne
  list<string> l_tamp_int;
  list<string> l_tamp_out;


  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  ifstream infile;
  infile.open("Test_lecture.dot", fstream::in); //ouverture du fichier .dot en mode lecture


  ////////////////////////////////////////////////////////////////////////////////
  //RECHERCHE DES NOMS ET CREATION DES OBJETS
  ////////////////////////////////////////////////////////////////////////////////

  //Recherche Gate
  //nom dans la liste gate
  //détection du nb d'entré
  //création de la classe

  //Recherche OUTPUT
  //nom dans la map avec le vector
  //nom dans la liste tampon

  //Recherc input
  //Nom dans une liste tanpon

  //Remplissage map_input avec les gates

  while(getline(infile, ligne)){
    cout << ligne << endl;
    if(ligne.find("\"INPUT\"") != string::npos){
      l_tamp_int.push_back(ligne.substr(0,ligne.find(" ")));

      cout << "ok_input" << endl;
    }
    else if(ligne.find("\"OUTPUT\"") != string::npos){
      l_tamp_out.push_back(ligne.substr(0,ligne.find(" ")));

      cout << "ok_output" << endl;
    }
    else{
      for(int i_v = 0; i_v < v_gate_avaible->size();i_v++){
        if(ligne.find(v_gate_avaible->at(i_v)) != string::npos){
          cout << ligne.substr(0,ligne.find(" ")) << endl;

          cout << "ok_gate" << endl;
        }
      }
    }
  }


  ////////////////////////////////////////////////////////////////////////////////
  //CREATION DES ENTRES SORTIE DES GATES
  ////////////////////////////////////////////////////////////////////////////////



  ////////////////////////////////////////////////////////////////////////////////
  //CONTROLE
  ////////////////////////////////////////////////////////////////////////////////


  //List tampon des noms des entrees
  // list<string>::iterator p =l_tamp_int.begin();
  // while(p != l_tamp_int.end()) {
  //   cout << *p << " "<<endl;
  //   p++;
  // }
  //

  //List tampon des noms des sortie
  // list<string>::iterator o =l_tamp_out.begin();
  // while(o != l_tamp_out.end()) {
  //   cout << *o << " "<<endl;
  //   o++;
  // }


  //  List des nom de portes disponible
  // for(int i_v = 0; i_v<v_gate_avaible->size();i_v++){
  //   cout << v_gate_avaible->at(i_v)<< endl;
  // }

  ////////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME
  ////////////////////////////////////////////////////////////////////////////////

  infile.close(); //fermeture fichier .dot


  //  cout << "FIN PRG"<<endl;
  return 0;
}
