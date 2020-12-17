#include "wavedrom.h"

using namespace std;

//Vérifie si le fichier de sortie est bien créé et que l'on peut l'utiliser
//return 0 si pas de problème sinon 1
bool check_open_file(const ofstream * infile){
  if(infile->is_open()){  //On teste si tout est OK après création du fichier
    return 0;
  }
  return 1;
}

int count_wave(const vector<int> *v_duree_delta){
  int nb_wave =0;
  for(int i = 0; i<v_duree_delta->size();i++){
    nb_wave = nb_wave + v_duree_delta->at(i);
  }
  return nb_wave;
}

//Rempli le wave en fonction du delta cycle
bool fill_wave(const vector<int> *v_duree_delta,const vector<string> *v_name,
  const map<string,vector<int>* > *m_val,ofstream * infile, const int * nb_wave){

    int count; //Compteur vérification nb stimulis
    for(int i = 0;i<v_name->size();i++){ //Boucle d'écriture des entrée
      count = 0;
      *infile<<"  {name: '"<<v_name->at(i)<<"', wave: '";

    for(int j = 0;j<v_duree_delta->size();j++){ // Boucle de chaque delta_cycle
      for(int k = 0;k<v_duree_delta->at(j);k++){
        if(j == 0){ //Initialisation première valeur du delta_cycle
          if(k == 0){
            *infile << m_val->at(v_name->at(i))->at(j);
          }
          else{ //Si la valeur avant le delta sycle est le même alors.
            *infile << ".";
          }
        }
        else if(m_val->at(v_name->at(i))->at(j) == m_val->at(v_name->at(i))->at(j-1)){
          *infile << ".";
        }
        else if(k == 0){
          *infile << m_val->at(v_name->at(i))->at(j);
        }
        else{
          *infile << ".";
        }
        count ++;
      }
    }
    if(count != *nb_wave){
      cout<<"Erreur d'écriture des valeurs des signaux d'entrée dans le fichier de sortie, il manque "<<
      nb_wave - count -1<<" valeur(s)"<<endl;
      return 1;
    }

    *infile << "'},"<<endl;
  }
  return 0;
}


//Main
int wavedrom_output(const vector<string> *v_input,const vector<string> * v_output,
  const vector<int> *v_duree_delta,const map<string,vector<int>* > *m_stimulis,
  const map<string,vector<int>* > *m_output,const string * s_path){

    //Check de la bonne extansion
    if(check_ext_path_json(s_path)){
        cout <<"Erreur, le fichier stimulis n'as pas l'extansion .json"<<endl;
      return 1;
    }

    //conversion du path de string à char pour fonction ouverture fichier
    char path[s_path->length()+1];
    strcpy(path,s_path->c_str());

    ofstream infile(path);

    //check ouverture fichier
    if(check_open_file(&infile)){
      cout << "Erreur: Impossible d'ouvrir le fichier de sortie."<< endl;
      return 1;
    }

    int nb_wave = count_wave(v_duree_delta); //Nomre total de stimulis

    infile << "{signal: [\n  ['Entrées',"<<endl; //En tête

    //Appel remplissage des entrée
    if(fill_wave(v_duree_delta,v_input,m_stimulis,&infile,&nb_wave)){
      return 1;
    }

    infile<<"  ],\n  {},\n  ['Sorties',"<<endl;

    //Appel remplissage des sorties
    if(fill_wave(v_duree_delta,v_output,m_output,&infile,&nb_wave)){
      return 1;
    }

    infile<<"  ],\n]}"<<endl; //Fin de fichier
    infile.close();
    return 0;
  }
