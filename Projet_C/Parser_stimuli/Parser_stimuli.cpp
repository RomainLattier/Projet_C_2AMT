#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "Parser_stimuli.h"

using namespace std;

//Vérification si l'entrée du stimulis est une entrée du circuit
bool verif_nom_exist(const string * nom,const vector<string> *v_in){
  for(int i = 0; i<v_in->size();i++){
    if(v_in->at(i) == *nom){
      return 0;
    }
  }
  return 1;
}

//Vérification si l'entrée du stimulis est une entrée du circuit
// bool verif_input__exist(const string * nom,const vector<string> *v_in){
//   for(int i = 0; i<v_in->size();i++){
//     if(v_in->at(i) == *nom){
//       return 0;
//     }
//   }
//   return 1;
// }

//Vérification si à un instant donnée, toutes les entrée ont la même valeur
bool verif_delta(const vector<string> *v_in, const map<string,vector<int>*> *m_tamp, const int * nb){
  for(int i = 0;i<v_in->size();i++){
    if(m_tamp->at(v_in->at(i))->at(*nb+1) != m_tamp->at(v_in->at(i))->at(*nb)){
      return 1;
    }
  }
  return 0;
}

int parser_stimuli(const vector<string> *v_in,vector<int> *v_delta,map<string,vector<int> *> *m_stimuli,const char * path){

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  map<string,vector<int>*> m_tamp;
  int nb_ligne = 0;
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
    string wave;
    if(ligne.find("name:") != string::npos){

      //Recherche du nom
      ligne_post = ligne.substr(ligne.find("'")+1,string::npos);
      nom = ligne_post.substr(0,ligne_post.find("'"));
      ligne_post = ligne_post.substr(ligne_post.find(",")+1,string::npos);

      //Verification du nom de l'entree
      if(verif_nom_exist(&nom,v_in)!=0){
        cout<<"Erreur de lecture du fichier wavedrom, l'entrée "<<nom<<
        " ne correspond pas à une entrée du circuit."<< endl;
        return 1;
      }

      // if(verif_input_exist(&nom,v_in)!=0){
      //   cout<<"Erreur de lecture du fichier wavedrom, l'entrée "<<nom<<
      //   " ne correspond pas à une entrée du circuit."<< endl;
      //   return 1;
      // }




      //Recherche des valeurs du signal
      if(ligne_post.find("wave:") != string::npos){
        ligne_post = ligne_post.substr(ligne_post.find("'")+1,string::npos);
        wave = ligne_post.substr(0,ligne_post.find("'"));
        vector<int> *v_wave = new vector<int>;
        vector<int> *v_w = new vector<int>;
        char point = '.';
        if(wave.at(0) == point){//remplace le point par 0 si première valeur, par défaut
          cout<<"Attention la première valeur de l'entrée "<<nom<<
          " n'est pas défini et elle a été remplacé par un 0."<<endl;
          wave.at(0) = '0';
        }
        for(int i = 0;i<wave.size();i++){
          if(i==0){
            v_w->push_back(wave.at(0) - '0');
            m_stimuli->insert(pair<string,vector<int>*>(nom,v_w));
          }

          if(wave.at(i) == point){ //remplace les point par la valeur précédente
            wave.at(i) = wave.at(i-1);
          }
          v_wave->push_back(wave.at(i) - '0');
        }
        m_tamp.insert(pair<string,vector<int>*>(nom,v_wave));
      }
      else{
        cout<<"Erreur, l'entrée "<<nom<<" n'a pas de valeur attribué."<<endl;
        return 1;
      }
      for(int i = 1;i<m_tamp.size();i++){
        if(m_tamp.at(v_in->at(i-1))->size() != m_tamp.at(v_in->at(i))->size()){
          cout << "Erreur, la durée du signal de l'entrée "<<v_in->at(i)<<
          " n'est pas de la même que la durée du signal de l'entrée "<< v_in->at(i-1)<<endl;
          return 1;
        }
      }
    }
  }


  //Delta cycle
  int cpt = 1;
  for(int i = 0;i<m_tamp.at(v_in->at(0))->size()-1;i++){
    if(verif_delta(v_in,&m_tamp,&i) == 0){
      cpt += 1;
    }
    else{
      v_delta->push_back(cpt);
      cpt = 1;
    }
  }
  v_delta->push_back(cpt);


  /////////////////////////////////////////////////////////////////////////////
  //CONTROLE
  /////////////////////////////////////////////////////////////////////////////

  for(int i = 0;i<v_in->size();i++){
    cout <<"l'entrée "<< v_in->at(i) <<" a pour valeur :"<<endl;
    for(int j = 0; j<m_tamp.at(v_in->at(i))->size();j++){
      cout << m_tamp.at(v_in->at(i))->at(j) <<endl;
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME
  /////////////////////////////////////////////////////////////////////////////


  for(int i = 0;i<v_in->size();i++){
  //  cout << "Destruction du stimuli tampon d'entrée "<<v_in->at(i)<<endl;
    delete m_tamp.at(v_in->at(i));
  }

  infile.close(); //fermeture fichier .dot

  return 0;
}
