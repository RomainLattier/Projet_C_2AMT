#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <stdlib.h>

#include "Parser_stimuli.h"
#include "../Parser_gate/Parser_gate.h"


using namespace std;

/////////////////////////////////////////////////////////////////////////////
//Fonction du parser stimuli
/////////////////////////////////////////////////////////////////////////////

//Vérification de l'extansion du fichier
bool check_ext_path_json(const string * s_path){
  if(s_path->find(".json") == string::npos){
    return 1;
  }
  return 0;
}

//Vérification de la syntaxe du fichier
bool verif_syntaxe(ifstream * infile){
  int n = 0;
  int nb_ligne = 0;
  int nb_ligne_tot = 0;
  int nb_saut = 0; //Compteur pour détecter fichier vide
  string ligne;

  infile->clear();
  infile->seekg(0);

  while(getline(*infile, ligne)){ // Mesure du nombre de ligne total
    nb_ligne_tot ++;
  }
  if(nb_ligne_tot == 0){
    cout<<"\nErreur, le fichier des stimulis est vide."<<endl;
    return 1;
  }
  infile->clear();
  infile->seekg(0);

  while(getline(*infile, ligne)){
    nb_ligne ++;
    remove_space(&ligne,&nb_ligne);
    if(ligne.size() == 0 || ligne.find("//") == 0 || ligne.find("{},") == 0){
      nb_saut++;
      if(nb_ligne_tot == nb_saut){
        cout<<"\nErreur, le fichier de structure du circuit est vide."<<endl;
        return 1;
      }
    }
    else{
      if(ligne.find("(") != string::npos || ligne.find(")") != string::npos
      || ligne.find("#") != string::npos
      || ligne.find("~") != string::npos || ligne.find("&") != string::npos
      || ligne.find("¬") != string::npos || ligne.find("²") != string::npos
      || ligne.find("é") != string::npos || ligne.find("è") != string::npos
      || ligne.find("`") != string::npos || ligne.find("|") != string::npos
      || ligne.find("ç") != string::npos || ligne.find("^") != string::npos
      || ligne.find("@") != string::npos || ligne.find("à") != string::npos
      || ligne.find("°") != string::npos || ligne.find("+") != string::npos
      || ligne.find("$") != string::npos || ligne.find("£") != string::npos
      || ligne.find("¤") != string::npos || ligne.find("*") != string::npos
      || ligne.find("µ") != string::npos || ligne.find("%") != string::npos
      || ligne.find("ù") != string::npos || ligne.find("§") != string::npos
      || ligne.find("!") != string::npos || ligne.find(">") != string::npos
      || ligne.find("-") != string::npos || ligne.find("<") != string::npos
      || ligne.find("?") != string::npos){
        cout<<"\nErreur de syntaxe, caractère interdit ligne "<<nb_ligne<<endl;
        cout<<"Caractère interdit: ( ) ' # ~ & ¬ ² é è ç ` | ^ @ à ° + $ £ ¤ * µ % ù § ! ? < > -"<<endl;
        return 1;
      }
      else{
        switch (n) {
          case 0 : //Début du fichier
          if(ligne.find("{signal:[") == string::npos){
            cout<<"Erreur de syntaxe, ligne "<<nb_ligne<<". Format attendu : {signal:["<<endl;
            return 1;
          }
          n =1;
          break;

          case 1 : //Chaque ligne de signaux
          if(nb_ligne == nb_ligne_tot){ //Cas dernière ligne
            if(ligne.find("]}") == string::npos){
              cout<<"Erreur de syntaxe à la fin du fichier, ligne "<<nb_ligne<<". Format attendu : ]}"<<endl;
              return 1;
            }
            infile->clear();
            infile->seekg(0);
            return 0;
            break;
          }
          if(ligne.find("{name:'") == string::npos){
            cout<<"Erreur de syntaxe au début de la ligne "<<nb_ligne<<
            ". Format attendu : {name:'"<<endl;
            return 1;
          }
          if(ligne.find(",wave:'") == string::npos){
            cout<<"Erreur de syntaxe au milieu de la ligne "<<nb_ligne<<
            ". Format attendu : ,wave:'"<<endl;
            return 1;
          }
          if(nb_ligne  == nb_ligne_tot -1 ){
            if(ligne.find("'}") == string::npos){
              cout<<"Erreur de syntaxe à la fin de la ligne "<<nb_ligne<<
              ". Format attendu : '}"<<endl;
              return 1;
            }
            ligne = ligne.substr(ligne.find(",wave:'") + 9,ligne.find("'}")-ligne.find(",wave:'") - 9);
          }
          else if(ligne.find("'},") == string::npos){
            cout<<"Erreur de syntaxe à la fin de la ligne "<<nb_ligne<<
            ". Format attendu : '},"<<endl;
            return 1;
          }
          if(nb_ligne  < nb_ligne_tot -1 ){
            ligne = ligne.substr(ligne.find(",wave:'") + 9,ligne.find("'},")-ligne.find(",wave:'") - 9);
          }
          for(int i = 0; i<ligne.size();i++){
            if(ligne.at(i) == '0'){
            }
            else if(ligne.at(i) == '1'){
            }
            else if(ligne.at(i) == '.'){
            }
            else {
              cout<<"Errer de syntaxe dans les valeurs du stimuli ligne "
              <<nb_ligne<<" valeur "<<i+1<<", valeur "<<ligne.at(i)<<
              " non reconnu."<<endl;
              return 1;
            }
          }
          break;
        }
      }
    }
  }
  cout<<"Erreur de sortie de la vérification de la syntaxe."<<endl;
  return 1;
}

//Recherche si un string est présent dans un vector de string
//return 0 si trouvé, 1 si pas trouvé
bool find_vector(const vector<string> * vector,const string * nom){
  for(int i = 0; i<vector->size();i++){
    if(vector->at(i) == *nom){
      return 0;
    }
  }
  return 1;
}

//Vérification si l'entrée du stimulis est une entrée du circuit et si toutes
//les entrée du circuit à une valeur
//retourne 0 si pas d'erreur détecté ou 1 si une erreur est détecté

bool verif_nom_input(ifstream * infile,const vector<string> *v_in){
  vector<string> v_name; //vector des noms des entrées trouvé dans le fichier
  int nb_ligne = 0; // Compteur de ligne
  string ligne;

  //remplissage vector name avec les nom de chaque entrée trouvé dans le fichier
  while(getline(*infile, ligne)){
    //    cout<<ligne<<endl;
    if(ligne.find("name:") != string::npos){

      //Recherche du nom
      ligne = ligne.substr(ligne.find("'")+1,string::npos);
      v_name.push_back(ligne.substr(0,ligne.find("'")));

      //Vérification si l'entrée du stimuli est une entrée du circuits
      if(find_vector(v_in,&v_name.back())==1){
        cout << "\nErreur, l'entrée " << v_name.back() << " n'est pas présente dans le circuit, ligne "<<nb_ligne<<endl;
        return 1;
      }
    }
    nb_ligne ++;

  }
  //Vérification si toutes les entrées du circuits sont adressé
  for(int i = 0; i<v_in->size();i++){
    if(find_vector(&v_name,&(v_in->at(i)))==1){
      cout << "\nErreur, l'entrée " << v_in->at(i) << " du circuit n'a pas de valeur affecté."<< endl;
      return 1;
    }
  }
  infile->clear();
  infile->seekg(0);
  return 0;
}

//Vérification si à un instant donnée, toutes les entrée ont la même valeur que la valeur prochaine
bool verif_delta(const vector<string> *v_in, const map<string,vector<int>*> *m_tamp, const int * nb){
  for(int i = 0;i<v_in->size();i++){
    if(m_tamp->at(v_in->at(i))->at(*nb+1) != m_tamp->at(v_in->at(i))->at(*nb)){
      return 1;
    }
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
//Parser main
/////////////////////////////////////////////////////////////////////////////

int parser_stimuli(const vector<string> *v_in,vector<int> *v_delta,map<string,vector<int> *> *m_stimuli,const string * s_path){

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER, définition variable et check de l'ouverture, du path et syntaxe
  ////////////////////////////////////////////////////////////////////////////////

  map<string,vector<int>*> m_tamp; //map tampon pour les valeurs des signaux avant delta_cycle
  int nb_ligne = 0; //Compteur de ligne
  string nom; //nom de l'entrée
  string wave; //valeurs du signal

  string ligne;
  ifstream infile;

  //Check de la bonne extansion
  if(check_ext_path_json(s_path)){
    cout <<"Erreur, le fichier stimulis n'as pas l'extansion .json"<<endl;
    return 1;
  }

  //conversion du path de string à char pour fonction ouverture fichier
  char path[s_path->length()+1];
  strcpy(path,s_path->c_str());

  infile.open(path, fstream::in); //ouverture du fichier en mode lecture

  //Check de la bonne ouverture du fichier
  if(check_open_file(&infile)){
    cout<<"stimulis."<<endl;
    return 1;
  }

  //Verification de la syntaxe du fichier
  if(verif_syntaxe(&infile)==1){return 1;
  }

  infile.clear();
  infile.seekg(0);

  /////////////////////////////////////////////////////////////////////////////
  //RECHERCHE DES NOMS ENTREES
  /////////////////////////////////////////////////////////////////////////////

  //Verification des nom des entrees
  if(verif_nom_input(&infile,v_in)==1){
    return 1;
  }

  //Extraction des entrées et de leurs valeurs
  while(getline(infile, ligne)){
    nb_ligne ++;
    remove_space(&ligne,&nb_ligne);
    if(ligne.size() == 0 || ligne.find("//") == 0 || ligne.find("{},") == 0){}
    else{
      if(ligne.find("name:") != string::npos){

        //Recherche du nom
        ligne = ligne.substr(ligne.find("'")+1,string::npos);
        nom = ligne.substr(0,ligne.find("'")); //Extraction du nom de l'entrée
        ligne = ligne.substr(ligne.find(",")+1,string::npos);

        /////////////////////////////////////////////////////////////////////////////
        //Recherche des valeurs des signaux
        /////////////////////////////////////////////////////////////////////////////

        if(ligne.find("wave:") != string::npos){
          ligne = ligne.substr(ligne.find("'")+1,string::npos);
          wave = ligne.substr(0,ligne.find("'"));//Extraction du signal
          vector<int> *v_wave = new vector<int>; // Vector tampon
          vector<int> *v_w = new vector<int>; //vector de la map stimulis, vide
          char point = '.';
          if(wave.at(0) == point){//remplace le point par 0 si première valeur, par défaut
            cout<<"Attention la première valeur de l'entrée "<<nom<<
            " n'est pas défini et elle a été remplacé par un 0, ligne "<<nb_ligne
            <<endl;
            wave.at(0) = '0';
          }
          for(int i = 0;i<wave.size();i++){
            if(i==0){ // Initialisation de la map stimuli avec un vector vide
              m_stimuli->insert(pair<string,vector<int>*>(nom,v_w));
            }

            if(wave.at(i) == point){ //remplace les point par la valeur précédente
              wave.at(i) = wave.at(i-1);
            }
            v_wave->push_back(wave.at(i) - '0'); //remplissage du vector tampon avec toutes les valeurs
          }
          m_tamp.insert(pair<string,vector<int>*>(nom,v_wave));//Remplissage de la map tampon avec le vector
        }
        else{ //Si pas de wave avec erreur
          cout<<"Erreur, l'entrée "<<nom<<" n'a pas de valeur attribué, ligne "<<
          nb_ligne<<endl;
          return 1;
        }
      }
    }
  }

  //Vérification si tout les signaux font la mêmes durée (nombre de stimulis)
  for(int i = 1;i<m_tamp.size();i++){
    if(m_tamp.at(v_in->at(i-1))->size() != m_tamp.at(v_in->at(i))->size()){
      cout << "Erreur, la durée du signal de l'entrée "<<v_in->at(i)<<
      " n'est pas la même que le signal de l'entrée "<< v_in->at(i-1)<<endl;
      return 1;
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  //Calcul du delta_cycle
  /////////////////////////////////////////////////////////////////////////////

  //Détermination des delta_cycle
  //Ecrit dans le vecteur v_delta la durée de chaque delta_cycle
  //le nombre de delta_cycle est identique au nombre de signaux dans la map stimulis
  //donc pour chaque signaux, on a une durée de ce signaux
  //Une durée peut être de 1 unité de temps et il est donc rentrée comme un delta_cycle de 1

  int cpt = 1; //Compteur de delta_cycle
  for(int i = 0;i<m_tamp.at(v_in->at(0))->size()-1;i++){
    if(verif_delta(v_in,&m_tamp,&i) == 0){
      cpt ++; //Si élément i = i+1 alors delta_cycle+1
    }
    else{
      v_delta->push_back(cpt); //Enregistrement de la durée du delta_cycle
      for(int j = 0;j<v_in->size();j++){ //Enregistrement des valeurs en entrées à l'instant i
      m_stimuli->at(v_in->at(j))->push_back(m_tamp.at(v_in->at(j))->at(i));
    }
    cpt = 1; //reset delta_cycle car lesentrées changent
  }
}
//Pour la dernière valeur du vector
v_delta->push_back(cpt);
for(int j = 0;j<v_in->size();j++){
  m_stimuli->at(v_in->at(j))->push_back(m_tamp.at(v_in->at(j))->at(m_tamp.at(v_in->at(0))->size()-1));
}

/////////////////////////////////////////////////////////////////////////////
//FIN PROGRAMME et delete des tampons dynamiques
/////////////////////////////////////////////////////////////////////////////

//delete des vector dynamique dans la map tampon
for(int i = 0;i<v_in->size();i++){
  //  cout << "Destruction du stimuli tampon d'entrée "<<v_in->at(i)<<endl;
  delete m_tamp.at(v_in->at(i));
}

infile.close(); //fermeture fichier .dot

return 0;
}
