#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "../Porte/Combinatoire/And.h"

using namespace std;

int parser_gate(map<string,list<Gate *> > *m_input,map<string,vector<int> > *m_output,vector<Gate *> *v_gate) {

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
    else if(ligne.find("\"AND") != string::npos){
      string nom = ligne.substr(0,ligne.find(" "));
      int nb_carac = ligne.find("\"AND");
      cout << stoi(ligne.substr(nb_carac + 4,1))<<endl;
  //    And * ptr_obj = new And(nom,(int)ligne.substr(nb_carac + 4,1));
  //    cout << ptr_obj->getName()<<endl;
      cout << "ok_gate" << endl;
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


////////////////////////////////////////////////////////////////////////////////
//TEST
////////////////////////////////////////////////////////////////////////////////
//Convertion de string en majuscules

// string str = "a";
// cout << str<<endl;
// transform(str.begin(), str.end(), str.begin(), ::toupper);
// cout << str<<endl;


// for(int i_v = 0; i_v < v_gate_avaible->size();i_v++){
//   string type_gate = v_gate_avaible->at(i_v);
//   if(ligne.find("\"" + type_gate) != string::npos){
//     string nom_gate = ligne.substr(0,ligne.find(" "));
