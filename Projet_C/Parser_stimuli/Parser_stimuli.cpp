#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "Parser_stimuli.h"

using namespace std;


bool verif_nom(const string * nom,const vector<string> *v_in){
  for(int i = 0; i<v_in->size();i++){
    if(v_in->at(i) == *nom){
      return 0;
    }
  }
  return 1;
}





int parser_stimuli(const vector<string> *v_in,vector<int> *v_delta,map<string,vector<int> *> *m_stimuli,const char * path){

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  string ligne;
  ifstream infile;
  infile.open(path, fstream::in); //ouverture du fichier .dot en mode lecture

  ////////////////////////////////////////////////////////////////////////////////
  //RECHERCHE DES NOMS ENTREES
  ////////////////////////////////////////////////////////////////////////////////


  while(getline(infile, ligne)){
    cout << ligne << endl;
    string ligne_post;
    string nom;
    if(ligne.find("name:") != string::npos){

      //Recherche du nom
      ligne_post = ligne.substr(ligne.find("'")+1,string::npos);
      nom = ligne_post.substr(0,ligne_post.find("'"));

      //Verification du nom de l'entree
      if(verif_nom(&nom,v_in)!=0){
        cout<<"Erreur de lecture du fichier wavedrom, l'entrée "<<nom<<
        " ne correspond pas à une entrée du circuit."<< endl;
        return 1;
      }

      //Recherche des valeurs du signal
      if(ligne_post.find("wave:") != string::npos){



      }
      else{
        cout<<"Erreur, l'entrée "<<nom<<" n'a pas de valeur attribué."<<endl;
        return 1;
      }

    }


    // else if(ligne.find("\"OUTPUT\"") != string::npos){
    //   string nom = ligne.substr(0,ligne.find(" "));
    //   v_out->push_back(nom);
    //   // vector<int> *ptr_v;
    //   // m_output[nom] = ptr_v;
    //   cout << "ok_output" << endl;
    // }
  }


  ////////////////////////////////////////////////////////////////////////////////
  //CONTROLE
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME
  ////////////////////////////////////////////////////////////////////////////////

  infile.close(); //fermeture fichier .dot

  return 0;
}
