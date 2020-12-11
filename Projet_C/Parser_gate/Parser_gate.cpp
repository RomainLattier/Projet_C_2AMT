#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>


#include "Parser_gate.h"
#include "../Porte/Combinatoire/And.h"
#include "../Porte/Combinatoire/Inv.h"
#include "../Porte/Combinatoire/Nand.h"
#include "../Porte/Combinatoire/Nor.h"
#include "../Porte/Combinatoire/Or.h"
#include "../Porte/Combinatoire/Xnor.h"
#include "../Porte/Combinatoire/Xor.h"


using namespace std;

//Recherche d'une valeur dans un vecteur

bool recherche_v(const string *nom_r,const vector<string> *v_base){
  for(int i = 0;i<v_base->size();i++){
    if(*nom_r == v_base->at(i)){
      return 1;
    }
  }
  return 0;
}

//Identifie le type entre sortie ou Gate
//entre type = 1;
//sorti type = 2;
//gate type = 3;
//return 1 si pas trouvé et 0 si trouvé

int recherche_type(int *type,const string *nom_r,const vector<string> *v_in, const vector<string> *v_out, const vector<string> *v_gate){
  if( recherche_v(nom_r,v_in) == 1){
    *type = 1;
    return 0;
  }
  else if( recherche_v(nom_r,v_out)==1){
    *type = 2;
    return 0;
  }
  else if( recherche_v(nom_r,v_gate)==1){
    *type = 3;
    return 0;
  }
  return 1;
}

//Recherche de l'index max de l element apres la fleche
//retourne l'index

bool recherche_index(bool * eol,const string * ligne,const int * index_min,const int * index_max){
  if(ligne->find(" ;") == string::npos){
    string ligne_post = ligne->substr(*index_min + 4,string::npos);
    cout << ligne_post <<endl;
    int index_1 = ligne_post.find(" ");
    int index_2 = ligne_post.find(";");
    cout << index_1<<endl;
    cout << ligne_post.substr(0,index_1)<<endl;
    cout << index_2<<endl;
    cout << ligne_post.substr(0,index_2)<<endl;
    if(index_1 == -1 && index_1 < index_2){
      *eol = 1;
      return index_2;
    }
    // else if(index)
  }
  else{
    cout << "Erreur de syntaxe à la fin de ligne"<<endl;
  }
  return 1;
}

//Parser main

int parser_gate(map<string,list<Gate *> > *m_input,map<string,vector<int>* > *m_output,vector<Gate *> *v_gate, map<string, Gate*> *m_tamp_output,vector<string> *v_in,vector<string> *v_out, char * path) {

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  vector<string> v_name_gate;
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
    string nom = ligne.substr(0,ligne.find(" "));
    if(ligne.find("\"INPUT\"") != string::npos){
      v_in->push_back(nom);

      cout << "ok_input" << endl;
    }
    else if(ligne.find("\"OUTPUT\"") != string::npos){
      v_out->push_back(nom);
      vector<int> * ptr_v = new vector<int>();
      m_output->insert(pair<string,vector<int>* >(nom,ptr_v) );
      cout << "ok_output" << endl;
    }

    //Detection du type des portes
    //Pour ajout de porte, il faut modifier les noms dans les find() avec le
    // nom a rechercher dans le fichier .dot, changer le type de l'objet a creer
    // avec le type de la porte ajoute et changer la taille dans
    // (int)ligne.substr(ligne.find("\"AND") + x,1)
    // ou x est le nombre de caractere da,s la recherche find()

    else if(ligne.find("\"AND") != string::npos){
      And * ptr_obj = new And(nom,(int)ligne.substr(ligne.find("\"AND") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"INV") != string::npos){
      Inv * ptr_obj = new Inv(nom,1);
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"NAND") != string::npos){
      Nand * ptr_obj = new Nand(nom,(int)ligne.substr(ligne.find("\"NAND") + 5,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"NOR") != string::npos){
      Nor * ptr_obj = new Nor(nom,(int)ligne.substr(ligne.find("\"NOR") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"Or") != string::npos){
      Or * ptr_obj = new Or(nom,(int)ligne.substr(ligne.find("\"OR") + 3,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"XNOR") != string::npos){
      Xnor * ptr_obj = new Xnor(nom,(int)ligne.substr(ligne.find("\"XNOR") + 5,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
    else if(ligne.find("\"XOR") != string::npos){
      Xor * ptr_obj = new Xor(nom,(int)ligne.substr(ligne.find("\"XOR") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
      cout << "ok_gate" << endl;
    }
  }

  infile.clear();
  infile.seekg(0);

  ////////////////////////////////////////////////////////////////////////////////
  //CREATION DES ENTRES SORTIE DES GATES
  ////////////////////////////////////////////////////////////////////////////////

  while(getline(infile, ligne)){
    cout << ligne << endl;
    if(ligne.find("->") != string::npos){
      bool eol = 0;

      int index = ligne.find(" ");
      string nom_r_b = ligne.substr(0,index); //nom a gauche de la fleche
      int type_b = 0;
      if(recherche_type(&type_b,&nom_r_b,v_in,v_out,&v_name_gate)!=0){
        cout<<"Erreur de lecture du fichier .dot, nom non reconnu caractère : "<< infile.tellg() << endl;
        return 1;
      }
      recherche_index(&eol,&ligne,&index);
      // string nom_r_a = ligne.substr(index + 4,); //nom a droite de la fleche
      // cout << nom_r_a << endl;
      // int type_a = 0;
      // if(recherche_type(&type_b,&nom_r_b,v_in,v_out,&v_name_gate)!=0){
      //   cout<<"Erreur de lecture du fichier .dot, nom non reconnu caractère : "<< infile.tellg() << endl;
      //   return 1;
      // }
    }
  }


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
