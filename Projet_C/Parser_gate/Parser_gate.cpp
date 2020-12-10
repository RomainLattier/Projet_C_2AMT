#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "../Porte/Combinatoire/And.h"
#include "../Porte/Combinatoire/Inv.h"
#include "../Porte/Combinatoire/Nand.h"
#include "../Porte/Combinatoire/Nor.h"
#include "../Porte/Combinatoire/Or.h"
#include "../Porte/Combinatoire/Xnor.h"
#include "../Porte/Combinatoire/Xor.h"


using namespace std;

int parser_gate(map<string,list<Gate *> > *m_input,map<string,vector<int> > *m_output,vector<Gate *> *v_gate, vector<Gate*> *v_tamp_output,vector<string> *v_int,vector<string> *v_out, char * path) {

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  string ligne;
  ifstream infile;
  infile.open(path, fstream::in); //ouverture du fichier .dot en mode lecture

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

  while(getline(infile, ligne)){
    cout << ligne << endl;
    if(ligne.find("\"INPUT\"") != string::npos){
      v_int->push_back(ligne.substr(0,ligne.find(" ")));

      cout << "ok_input" << endl;
    }
    else if(ligne.find("\"OUTPUT\"") != string::npos){
      string nom = ligne.substr(0,ligne.find(" "));
      v_out->push_back(nom);
      // vector<int> *ptr_v;
      // m_output[nom] = ptr_v;
      cout << "ok_output" << endl;
    }

    //Detection du type des portes
    //Pour ajout de porte, il faut modifier les noms dans les find() avec le
    // nom a rechercher dans le fichier .dot, changer le type de l'objet a creer
    // avec le type de la porte ajoute et changer la taille dans
    // (int)ligne.substr(ligne.find("\"AND") + x,1)
    // ou x est le nombre de caractere da,s la recherche find()


    else if(ligne.find("\"AND") != string::npos){
      And * ptr_obj = new And(ligne.substr(0,ligne.find(" ")),(int)ligne.substr(ligne.find("\"AND") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"INV") != string::npos){
      Inv * ptr_obj = new Inv(ligne.substr(0,ligne.find(" ")),1);
      v_gate->push_back(ptr_obj);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"NAND") != string::npos){
      Nand * ptr_obj = new Nand(ligne.substr(0,ligne.find(" ")),(int)ligne.substr(ligne.find("\"NAND") + 5,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"NOR") != string::npos){
      Nor * ptr_obj = new Nor(ligne.substr(0,ligne.find(" ")),(int)ligne.substr(ligne.find("\"NOR") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"Or") != string::npos){
      Or * ptr_obj = new Or(ligne.substr(0,ligne.find(" ")),(int)ligne.substr(ligne.find("\"OR") + 3,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"XNOR") != string::npos){
      Xnor * ptr_obj = new Xnor(ligne.substr(0,ligne.find(" ")),(int)ligne.substr(ligne.find("\"XNOR") + 5,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"XOR") != string::npos){
      Xor * ptr_obj = new Xor(ligne.substr(0,ligne.find(" ")),(int)ligne.substr(ligne.find("\"XOR") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
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

  ////////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME
  ////////////////////////////////////////////////////////////////////////////////

  infile.close(); //fermeture fichier .dot

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
