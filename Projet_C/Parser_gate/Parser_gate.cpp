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
#include "../Porte/Gate_out.h"

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
bool recherche_type(int *type,const string *nom_r,const vector<string> *v_in,
   const vector<string> *v_out, const vector<string> *v_gate){

  if(recherche_v(nom_r,v_in) == 1){ //Recherche si l'element est une entree
    *type = 1;
    return 0;
  }

  else if(recherche_v(nom_r,v_out)==1){//Recherche si l'element est une sortie
    *type = 2;
    return 0;
  }

  else if(recherche_v(nom_r,v_gate)==1){//Recherche si l'element est une porte
    *type = 3;
    return 0;
  }

  return 1;
}

//Recherche de l'index max de l element apres la fleche
//retourne l'index
//Recherche l'espace ou le point virgule le plus proche

bool recherche_nom_suivant(bool * eol,const string * ligne, int * index_min, string *nom){
  if(ligne->find(" ;") == string::npos || ligne->find(";") == string::npos){

    string ligne_post = ligne->substr(*index_min,string::npos);
    int index_1 = ligne_post.find(" "); //Si pas d'espace alors index_1 = -1
    int index_2 = ligne_post.find(";");//index_2 toujours supérieur a index_1

    //cas ou on est en fin de ligne
    if(index_1 == -1){
      *eol = 1; //Flag fin de la ligne pour prochaine boucle
      *nom = ligne_post.substr(0,index_2);
      return 0;
    }

    //Cas on n'est pas en fin de ligne
    else if(index_1 < index_2){
      *nom = ligne_post.substr(0,index_1);
      return 0;
    }
  }

  else{
    cout << "Erreur de syntaxe à la fin de la ligne" <<endl;
    return 1;
  }
  return 0;
}
//Possible optimisation avec index2 tester si string::npos -1 marche
//Detection avec \n au lieu de ";"

//Remplissage de la map input avec en clé le nom de input et en valeur le
//pointeur vers les premières portes

bool link_m_input( map<string, vector<Gate*>* > *m_input, vector<Gate*> *v_gate,
  const string *nom_r_1,const string *nom_r_2){

  if(m_input->count(*nom_r_1) != 0){ //Si entree deja dans la map, cas input sur plusieur portes
    for(int i = 0;i<v_gate->size();i++){

      if(v_gate->at(i)->getName() == *nom_r_2){
        m_input->find(*nom_r_1)->second->push_back(v_gate->at(i));
      }
    }
  }
  else{//entre pas encore cree
    vector<Gate *> * ptr_v_in = new vector<Gate *>();
    cout << "Création de l'entrée "<< *nom_r_1 << endl;
    for(int i = 0;i<v_gate->size();i++){
      if(v_gate->at(i)->getName() == *nom_r_2){

        ptr_v_in->push_back(v_gate->at(i));
        m_input->insert(pair<string,vector<Gate*>* >(*nom_r_1,ptr_v_in) );
      }
    }
  }
  return 0;
}

//Remplissage de la map tampon output avec en clé le nom de output et en valeur le
//pointeur vers la porte tampon

bool link_m_tamp_output(map<string, Gate*> *m_tamp_output,vector<Gate*> *v_gate,
  const string *nom_r_1,const string *nom_r_2){

  if(m_tamp_output->count(*nom_r_1) == 0){//Verification pas deja cree
    Gate_out * ptr_gate_tamp = new Gate_out(*nom_r_2,1);

    for(int i = 0;i<v_gate->size();i++){ //Recherche du pointeur de la gate a gauche
      if(v_gate->at(i)->getName() == *nom_r_1){

        v_gate->at(i)->add_output(ptr_gate_tamp);
        m_tamp_output->insert(pair<string,Gate* >(*nom_r_2,ptr_gate_tamp) );
      }
    }
  }
}


//Parser main

int parser_gate(map<string,vector<Gate *>* > *m_input,map<string,vector<int>* > *m_output,
  vector<Gate *> *v_gate, map<string, Gate*> *m_tamp_output,vector<string> *v_in,
  vector<string> *v_out, char * path) {

  /////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  /////////////////////////////////////////////////////////////////////////////

  vector<string> v_name_gate;
  string ligne;
  ifstream infile;
  infile.open(path, fstream::in); //ouverture du fichier .dot en mode lecture

  /////////////////////////////////////////////////////////////////////////////
  //RECHERCHE DES NOMS ET CREATION DES OBJETS
  /////////////////////////////////////////////////////////////////////////////

  while(getline(infile, ligne)){
    //    cout << ligne << endl;
    string nom = ligne.substr(0,ligne.find(" "));
    if(ligne.find("\"INPUT\"") != string::npos){
      v_in->push_back(nom);
    }

    else if(ligne.find("\"OUTPUT\"") != string::npos){
      v_out->push_back(nom);
      vector<int> * ptr_v = new vector<int>();
      m_output->insert(pair<string,vector<int>* >(nom,ptr_v) );
      cout << "Création de la sortie "<< nom << endl;
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
    }

    else if(ligne.find("\"INV") != string::npos){
      Inv * ptr_obj = new Inv(nom,1);
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
    }

    else if(ligne.find("\"NAND") != string::npos){
      Nand * ptr_obj = new Nand(nom,(int)ligne.substr(ligne.find("\"NAND") + 5,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
    }

    else if(ligne.find("\"NOR") != string::npos){
      Nor * ptr_obj = new Nor(nom,(int)ligne.substr(ligne.find("\"NOR") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
    }

    else if(ligne.find("\"OR") != string::npos){
      Or * ptr_obj = new Or(nom,(int)ligne.substr(ligne.find("\"OR") + 3,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
    }

    else if(ligne.find("\"XNOR") != string::npos){
      Xnor * ptr_obj = new Xnor(nom,(int)ligne.substr(ligne.find("\"XNOR") + 5,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
    }

    else if(ligne.find("\"XOR") != string::npos){
      Xor * ptr_obj = new Xor(nom,(int)ligne.substr(ligne.find("\"XOR") + 4,1).at(0)-'0');
      v_gate->push_back(ptr_obj);
      v_name_gate.push_back(nom);
    }
  }

  infile.clear();
  infile.seekg(0);

  ////////////////////////////////////////////////////////////////////////////////
  //CREATION DES ENTRES SORTIE DES GATES
  ////////////////////////////////////////////////////////////////////////////////

  while(getline(infile, ligne)){
    //    cout << ligne << endl;
    if(ligne.find("->") != string::npos){
      bool eol = 0; //Flag fin de la ligne
      int index_min = 0; //init index sur le premier nom
      string nom_r_1 = ligne.substr(index_min,ligne.find(" ")); //extraction du premier nom a gauche de la fleche
      string nom_r_2;
      int type_1 = 0; //init du type du nom avant la fleche
      int type_2 = 0; //init a 0 pour le deuxieme
      if(recherche_type(&type_1,&nom_r_1,v_in,v_out,&v_name_gate)!=0){
        cout<<"Erreur de lecture du fichier .dot, nom non reconnu caractère : "<<
         infile.tellg() << endl;
        return 1;
      }

      while(eol == 0){
        //possible ajouter verification syntaxe " -> " !!!! espaces

        index_min += nom_r_1.size() + 4;
        if(recherche_nom_suivant(&eol,&ligne,&index_min,&nom_r_2)!=0){
          cout<<"Erreur de lecture du fichier .dot, caractère : "<< infile.tellg() << endl;
          return 1;
        }

        if(recherche_type(&type_2,&nom_r_2,v_in,v_out,&v_name_gate)!=0){
          cout<<"Erreur de lecture du fichier .dot, nom non reconnu caractère : "<<
           infile.tellg() << endl;
          return 1;
        }

        //Cas ou les deux elements sont des portes
        if(type_1 == 3 && type_2 == 3){
          for(int i = 0;i<v_gate->size();i++){ //Recherche du pointeur de la gate a gauche
            if(v_gate->at(i)->getName() == nom_r_1){
              for(int j = 0;j<v_gate->size();j++){ // Recherche du pointeur de la gate a droite
                if(v_gate->at(j)->getName() == nom_r_2){
                  v_gate->at(i)->add_output(v_gate->at(j)); //Affectation de la porte droite dans la porte gauche
                }
              }
            }
          }
        }

        //Cas element de gauche est une entre et element de droite une porte
        else if(type_1 == 1 && type_2 == 3){
          if(link_m_input(m_input,v_gate,&nom_r_1,&nom_r_2)!=0){
            cout<<"Erreur de lecture du fichier .dot, connection entre la porte "<<
             nom_r_1 <<" et la porte "<< nom_r_2 << " impossible, voir caractère : " <<
              infile.tellg() << endl;
            return 1;
          }
        }

        //cas ou element de gauche est une porte et element de droite est une sortie
        else if(type_1 == 3 && type_2 == 2){
          if(link_m_tamp_output(m_tamp_output,v_gate,&nom_r_1,&nom_r_2)!=0){
            cout<<"Erreur de lecture du fichier .dot, connection entre la porte "<<
             nom_r_1 <<" et la sortie "<< nom_r_2 << " impossible, voir caractère : " <<
              infile.tellg() << endl;
            return 1;
          }
        }

        //Cas ou element de gauche est une entre et element de droite une sortie
        else if(type_1 == 1 && type_2 == 2){
          cout<<"Attention, une entrée et directement connecté à une sortie."<<endl;

        }
        
        //Detection erreur si sortie sur une entre ou porte sur entre
        else if(type_2 == 1){
          cout << "Erreur de d'interconnexion dans la structure du circuit: une sorti est connecté à un INPUT."<<endl;
          cout << "Voir caractère : " << infile.tellg() << endl;
          return 1;
        }

        nom_r_1 = nom_r_2; //le deuxieme element devient le premier
        type_1 = type_2;

      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME
  ////////////////////////////////////////////////////////////////////////////////

  infile.close(); //fermeture fichier .dot

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//TEST &controle
////////////////////////////////////////////////////////////////////////////////
//controle des std::vector

// cout <<"\nv_name_gate :"<<endl;
// for(int i = 0; i<v_name_gate.size();i++){
//   cout << v_name_gate.at(i)<<endl;
// }
//
// cout <<"\nv_in :"<<endl;
// for(int i = 0; i<v_in->size();i++){
//   cout << v_in->at(i)<<endl;
// }
//
// cout <<"\nv_out :"<<endl;
// for(int i = 0; i<v_out->size();i++){
//   cout << v_out->at(i)<<endl;
// }

//Convertion de string en majuscules

// string str = "a";
// cout << str<<endl;
// transform(str.begin(), str.end(), str.begin(), ::toupper);
// cout << str<<endl;


// for(int i_v = 0; i_v < v_gate_avaible->size();i_v++){
//   string type_gate = v_gate_avaible->at(i_v);
//   if(ligne.find("\"" + type_gate) != string::npos){
//     string nom_gate = ligne.substr(0,ligne.find(" "));
