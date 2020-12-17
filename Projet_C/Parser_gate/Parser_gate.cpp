#include "Parser_gate.h"

using namespace std;

//initialisation des valeurs des input

bool check_ext_path_dot(const string * s_path){
  if(s_path->find(".dot") == string::npos){
    return 1;
  }
  return 0;
}

bool check_open_file(const ifstream * infile){
  if(infile->is_open()){  //On teste si tout est OK après création du fichier
    return 0;
  }
  else cout << "\nErreur, impossible d'ouvrir le fichier ";
  return 1;
}

//Suppression des espaces dans un string
bool remove_space(string * str, const int * nb_ligne){
  if(str->find("- >") != string::npos){
    cout<<"\nErreur de syntaxe, il y a un espace dans le séparateur -> ligne "<<*nb_ligne<<endl;
    return 1;
  }
  str->erase(remove(str->begin(), str->end(),' '), str->end());
  return 0;
}

//converti un nombre au format string en int
bool conv_int(const string a,int * b){
  for(int i = a.size(); i > 0;i--){
    if((a.at(i-1) - '0') > 9 || (a.at(i-1) - '0') < 0){
      return 1;
    }
    *b = *b + ((int)a.at(i-1) - '0')*pow(10,a.size()-i);
  }
  return 0;
}

bool find_name_in_vector(const string * name,const vector<string> * vector){
  for(int i = 0;i<vector->size();i++){
    string gate_r = "[label=" + vector->at(i);
    if(name->find(gate_r) != string::npos){return 0;}
  }
  return 1;
}


//Vérification de la syntaxe du fichier
bool check_syntaxe(ifstream * infile){
  int n = 0;
  int m = 0;
  int nb_ligne = 0;
  int nb_ligne_tot = 0;
  string ligne;
  vector<string> v_gate_name;
  v_gate_name.push_back("\"INPUT\"");
  v_gate_name.push_back("\"OUTPUT\"");
  v_gate_name.push_back("\"AND");
  v_gate_name.push_back("\"NOT");
  v_gate_name.push_back("\"NAND");
  v_gate_name.push_back("\"NOR");
  v_gate_name.push_back("\"OR");
  v_gate_name.push_back("\"XNOR");
  v_gate_name.push_back("\"XOR");
  v_gate_name.push_back("\"MUX");

  infile->clear();
  infile->seekg(0);

  while(getline(*infile, ligne)){ // Mesure du nombre de ligne total
    nb_ligne_tot ++;
  }
  infile->clear();
  infile->seekg(0);

  while(getline(*infile, ligne)){
    nb_ligne ++;
    if(remove_space(&ligne,&nb_ligne)){return 1;}
    //Si la ligne est un saut de ligne alors passe directement à la ligne suivante
    if(ligne.size() == 0 || ligne.find("//") == 0){
    }
    else{

      if(ligne.find("(") != string::npos || ligne.find(")") != string::npos
      || ligne.find("'") != string::npos || ligne.find("#") != string::npos
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
      || ligne.find("!") != string::npos || ligne.find(":") != string::npos
      || ligne.find(",") != string::npos || ligne.find("<") != string::npos
      || ligne.find("?") != string::npos){
        cout<<"\nErreur de syntaxe, caractère interdit ligne "<<nb_ligne<<endl;
        cout<<"Caractère interdit: ( ) ' # ~ & ¬ ² é è ç ` | ^ @ à ° + $ £ ¤ * µ % ù § ! ? : <"<<endl;
        return 1;
      }

      switch (n) {
        case 0 : //Début du fichier
        if(ligne.find("digraph") == string::npos){
          cout<<"\nErreur de syntaxe, ligne "<<nb_ligne<<". Format attendu : digraph nom_circuit {"<<endl;
          return 1;
        }
        if(ligne.find("{") != ligne.size()-1){
          cout<<"\nErreur de syntaxe, le séparateur ({) de fin de la ligne "
          <<nb_ligne<<". Format attendu : digraph nom_circuit {"<<endl;
          return 1;
        }
        n =1;
        break;

        case 1 : //Chaque ligne de signaux
        if(nb_ligne == nb_ligne_tot){ //Cas dernière ligne
          if(ligne.find("}") == string::npos){
            cout<<"\nErreur de syntaxe à la fin du fichier, ligne "<<nb_ligne<<". Format attendu : }"<<endl;
            return 1;
          }
          infile->clear();
          infile->seekg(0);
          return 0;
          break;
        }

        if(ligne.find(";") == string::npos){
          cout<<"\nErreur de syntaxe, indicateur de fin de ligne (;) non"<<
          " reconnu, ligne "<<nb_ligne<<endl;
          return 1;
        }

        if(ligne.find("//") != string::npos){
          if(ligne.find("//")>ligne.find(";")){
            ligne = ligne.substr(0,ligne.find(";")+1);
          }
          else{
            cout<<"\nErreur de syntaxe, un commentaire est placé avant "<<
            "l'indicateur de fin de ligne (;), ligne "<<nb_ligne<<endl;
            return 1;
          }
        }

        if(ligne.find("{") != string::npos || ligne.find("}") != string::npos){
          cout<<"\nErreur de syntaxe, caractère interdit ligne "<<nb_ligne<<endl;
          cout<<"Caractère interdit: { }"<<endl;
          return 1;
        }

        m = 0;
        while(m < 3){
          switch(m){

            case 0 :
            if(ligne.find("[label") != string::npos && ligne.find("->") == string::npos){
              m = 1;
              break;
            }
            else if(ligne.find("[label") == string::npos && ligne.find("->") != string::npos){
              m = 2;
              break;
            }
            else if(ligne.find("[label") == string::npos && ligne.find("->") == string::npos){
              cout<<"\nErreur de sémentique à la ligne "<<nb_ligne<<
              ", il manque le séparateur -> (pour définir les connexions)"<<
              " ou le séparateur au format : [label (pour définir les I/O et les portes)."<<endl;
              return 1;
            }
            else if(ligne.find("[label") != string::npos && ligne.find("->") != string::npos){
              cout<<"\nErreur de sémentique à la ligne "<<nb_ligne<<
              ", contradiction, il y a le séparateur -> (pour définir les connexions)"<<
              " et le séparateur label au format : [label (pour définir les I/O et les portes)."<<endl;
              return 1;
            }

            case 1 :
            if(ligne.find("-") != string::npos || ligne.find(">") != string::npos){
              cout<<"\nErreur de syntaxe, caractère interdit ligne "<<nb_ligne<<endl;
              cout<<"Caractère interdit: - >"<<endl;
              return 1;
            }
            if(ligne.find("[") == 0){
              cout<<"\nErreur de sémentique au début de la ligne "<<nb_ligne<<", aucun nom est défini."<<endl;
              return 1;
            }
            if(ligne.find("[label=") == string::npos){
              cout<<"\nErreur de syntaxe ligne "<<nb_ligne<<", il manque un égal après [label"<<endl;
              return 1;
            }
            if(find_name_in_vector(&ligne,&v_gate_name)){
              cout<<"\nErreur de sémentique, INPUT, OUTPUT ou porte logique non reconnu, ligne "
              <<nb_ligne<<". Voir argument après label=..."<<endl;
              return 1;
            }
            if(ligne.find("\"MUX2\"") != string::npos){
              if(ligne.find("[label=\"MUX2\"sel=\"") != string::npos){
                int taille_sel = ligne.find("\"];")-ligne.find("[label=\"MUX2\"sel=\"") - 18;
                if(taille_sel < 1){
                  cout<<"\nErreur de sémentique, le nom de la sélection est incomplète, ligne "<<nb_ligne<<endl;
                  return 1;
                }
              }
              else{
                cout<<"\nErreur de syntaxe, sélection du MUX non reconnu ligne "<<nb_ligne<<endl;
                return 1;
              }
            }
            if(ligne.find("\"];") == string::npos){
              cout<<"\nErreur de syntaxe à la fin de la ligne "<<nb_ligne
              <<", format attendu: \"];"<<endl;
              return 1;
            }
            m = 3;
            break;

            case 2 :
            if(ligne.find("->") == 0){
              cout<<"\nErreur de sémentique au début de la ligne "<<nb_ligne<<", aucun nom est défini."<<endl;
              return 1;
            }
            if(ligne.find("->->") != string::npos){
              cout<<"\nErreur de syntaxe, il y a du séparateur (->) de suite ligne "<<nb_ligne<<endl;
              return 1;
            }

            if(ligne.find("[") != string::npos || ligne.find("]") != string::npos){
              cout<<"\nErreur de syntaxe, caractère interdit ligne "<<nb_ligne<<endl;
              cout<<"Caractère interdit: [ ]"<<endl;
              return 1;
            }
            m = 3;
            break;
          }
        }
      }
    }
  }
  cout<<"\nErreur de sortie de la vérification de la syntaxe."<<endl;
  return 1;
}

//Check si le nom pas trop long et pas interdit
bool check_name(const string * nom, const vector<string> * vector){
  if(nom->size()>32){
    cout<<"\nErreur le nom :\n"<<*nom<<"\nest trop long, taille maximum autorisé de 32 caractères."<<endl;
    return 1;
  }
  for(int i =0;i<vector->size();i++){
    if(*nom == vector->at(i)){
      cout<<"\nErreur le nom "<<*nom<<"est un nom réservé."<<endl;
      return 1;
    }
  }
  return 0;
}

bool check_name_exist(const string *nom_r,const vector<string> *v_in,
  const vector<string> *v_out,const vector<string> *v_gate){
    int i = 0;
    if(recherche_type(&i,nom_r,v_in,v_out,v_gate) == 0){
      return 1;
    }
    return 0;
  }


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
  string ligne_post = ligne->substr(*index_min,string::npos);
  int index_1 = ligne_post.find("->"); //Si pas d'espace alors index_1 = -1
  int index_2 = ligne_post.find(";");//index_2 toujours supérieur a index_1

  //cas ou on est en fin de ligne
  if(index_1 == -1){
    *eol = 1; //Flag fin de la ligne pour prochaine boucle
    *nom = ligne_post.substr(0,index_2);
  }

  //Cas on n'est pas en fin de ligne
  else if(index_1 < index_2){
    *nom = ligne_post.substr(0,index_1);
  }
  return 0;
}

//Remplissage de la map input avec en clé le nom de input et en valeur le
//pointeur vers les premières portes
bool link_m_input(map<string, vector<Gate*>* > *m_input, vector<Gate*> *v_gate,
  const string *nom_r_1,const string *nom_r_2,const map<string, Gate*> *m_tamp_output){

    if(m_input->count(*nom_r_1) != 0){ //Si entree deja dans la map, cas input sur plusieur portes
      for(int i = 0;i<v_gate->size();i++){
        if(v_gate->at(i)->getName() == *nom_r_2){
          if(v_gate->at(i)->get_is_a_mux() && v_gate->at(i)->get_sel_name(0) != *nom_r_1){ //si c'est un mux
          v_gate->at(i)->add_gate_input(*nom_r_1);
        }
        m_input->find(*nom_r_1)->second->push_back(v_gate->at(i));
        return 0;
      }
    }
    m_input->find(*nom_r_1)->second->push_back(m_tamp_output->at(*nom_r_2));
    return 0;

  }
  else{//entre pas encore cree
    vector<Gate *> * ptr_v_in = new vector<Gate *>();
    //cout << "Création de l'entrée "<< *nom_r_1 << endl;
    for(int i = 0;i<v_gate->size();i++){
      if(v_gate->at(i)->getName() == *nom_r_2){
        if(v_gate->at(i)->get_is_a_mux() && v_gate->at(i)->get_sel_name(0) != *nom_r_1){ //si c'est un mux
        v_gate->at(i)->add_gate_input(*nom_r_1);
      }
      ptr_v_in->push_back(v_gate->at(i));
      m_input->insert(pair<string,vector<Gate*>* >(*nom_r_1,ptr_v_in) );
      return 0;
    }
  }
  ptr_v_in->push_back(m_tamp_output->at(*nom_r_2));
  m_input->insert(pair<string,vector<Gate*>* >(*nom_r_1,ptr_v_in) );
  return 0;
}
return 1;
}

//Remplissage de la map tampon output avec en clé le nom de output et en valeur le
//pointeur vers la porte tampon

bool link_m_tamp_output(map<string, Gate*> *m_tamp_output,vector<Gate*> *v_gate,
  const string *nom_r_1,const string *nom_r_2, const vector<string> * v_in){

    if(m_tamp_output->count(*nom_r_2) == 0){//Verification pas deja cree
      Gate_out * ptr_gate_tamp = new Gate_out(*nom_r_2,1);

      for(int i = 0;i<v_gate->size();i++){ //Recherche du pointeur de la gate a gauche
        if(v_gate->at(i)->getName() == *nom_r_1){

          v_gate->at(i)->add_output(ptr_gate_tamp);
          m_tamp_output->insert(pair<string,Gate* >(*nom_r_2,ptr_gate_tamp) );
          return 0;
        }
      }
      for(int i = 0; i < v_in->size(); i++){
        if(v_in->at(i) == *nom_r_1){
          m_tamp_output->insert(pair<string,Gate* >(*nom_r_2,ptr_gate_tamp) );
          return 0;
        }
      }
    }
    return 1;
  }

  //Lien entre deux portes
  bool link_double_gate(const vector<Gate *> *v_gate,const string *nom_r_1,const string *nom_r_2){
    for(int i = 0;i<v_gate->size();i++){ //Recherche du pointeur de la gate a gauche
      if(v_gate->at(i)->getName() == *nom_r_1){
        for(int j = 0;j<v_gate->size();j++){ // Recherche du pointeur de la gate a droite
          if(v_gate->at(j)->getName() == *nom_r_2){
            if(v_gate->at(j)->get_is_a_mux() && v_gate->at(j)->get_sel_name(0) != *nom_r_1){
              v_gate->at(j)->add_gate_input(*nom_r_1);
            }
            v_gate->at(i)->add_output(v_gate->at(j)); //Affectation de la porte droite dans la porte gauche
            return 0;
          }
        }
      }
    }
    return 1;
  }

  //Conversion de la map tampon en un vector

  bool change_map_to_vector(map<string,Gate*>* m_gate,vector<Gate*>* v_gate){
    for(map<string, Gate*>::iterator itr = m_gate->begin(); itr != m_gate->end(); itr++){
      v_gate->push_back(itr->second);
    }
  }


  //Parser main

  int parser_gate(map<string,vector<Gate *>* > *m_input,map<string,vector<int>* > *m_output,
    vector<Gate *> *v_gate, vector<Gate*> *v_tamp_output,vector<string> *v_in,
    vector<string> *v_out,const string * s_path) {

      /////////////////////////////////////////////////////////////////////////////
      //OUVERTURE FICHIER
      /////////////////////////////////////////////////////////////////////////////

      vector<string> v_name_gate;
      map<string, Gate*> m_tamp_output;
      map<string, Gate_mux *> m_tamp_mux;
      int nb_ligne = 1;
      bool flag_seq = 0; //flag si porte séquentiel créé
      string ligne;
      ifstream infile;

      vector<string> v_name_ban;
      v_name_ban.push_back("INPUT");
      v_name_ban.push_back("OUTPUT");
      v_name_ban.push_back("AND");
      v_name_ban.push_back("NOT");
      v_name_ban.push_back("NAND");
      v_name_ban.push_back("NOR");
      v_name_ban.push_back("OR");
      v_name_ban.push_back("XNOR");
      v_name_ban.push_back("XOR");
      v_name_ban.push_back("MUX");

      if(check_ext_path_dot(s_path)){
        cout <<"\nErreur, le fichier structure n'as pas l'extansion .dot"<<endl;
        return 1;
      }

      char path[s_path->length()+1];
      strcpy(path,s_path->c_str());

      infile.open(path, fstream::in); //ouverture du fichier .dot en mode lecture

      /////////////////////////////////////////////////////////////////////////////
      //RECHERCHE DES NOMS ET CREATION DES OBJETS
      /////////////////////////////////////////////////////////////////////////////

      if(check_open_file(&infile)){
        cout<<"structure."<<endl;
        return 1;
      }

      if(check_syntaxe(&infile)){return 1;}

      infile.clear();
      infile.seekg(0);

      while(getline(infile, ligne)){
        nb_ligne++;
        remove_space(&ligne,&nb_ligne);

        //Si la ligne est un saut de ligne alors passe directement à la ligne suivante
        if(ligne.size() == 0){}
        else{
          string nom = ligne.substr(0,ligne.find("["));
          if(check_name(&nom,&v_name_ban)){
            cout<<"Ligne "<<nb_ligne<<endl;
            return 1;
          }
          if(check_name_exist(&nom,v_in,v_out,&v_name_gate)){
            cout<<"\nErreur de sémentique, le nom "<<nom<<" est déjà utilisé, ligne "<<nb_ligne-1<<endl;
            return 1;
          }

          if(ligne.find("=\"INPUT\"];") != string::npos){
            v_in->push_back(nom);
          }

          else if(ligne.find("=\"OUTPUT\"];") != string::npos){
            v_out->push_back(nom);
            vector<int> * ptr_v = new vector<int>();
            m_output->insert(pair<string,vector<int>* >(nom,ptr_v) );
            //cout << "Création de la sortie "<< nom << endl;
          }

          //Detection du type des portes
          //Pour ajout de porte, il faut modifier les noms dans les find() avec le
          // nom a rechercher dans le fichier .dot, changer le type de l'objet a creer
          // avec le type de la porte ajouté et changer la taille dans
          // ligne.substr(ligne.find("\"AND") + X,ligne.find("\"];")-ligne.find("\"AND")-X)
          // ou X est le nombre de caractere da,s la recherche find()

          else if(ligne.find("[label=\"AND") != string::npos){
            int nb_entry = 0;
            if(conv_int(ligne.substr(ligne.find("[label=\"AND") + 11,ligne.find("\"];")-ligne.find("[label=\"AND")-11),&nb_entry)){
              cout<<"\nErreur de sémentique, le nombre d'entrée de la porte "<<
              nom<<" contient un caractère outre qu'un chiffre, ligne "<<nb_ligne<<endl;
              return 1;
            }
            And * ptr_obj = new And(nom,nb_entry);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"NOT") != string::npos){
            Inv * ptr_obj = new Inv(nom,1);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"NAND") != string::npos){
            int nb_entry = 0;
            if(conv_int(ligne.substr(ligne.find("[label=\"NAND") + 12,ligne.find("\"];")-ligne.find("[label=\"NAND")-12),&nb_entry)){
              cout<<"\nErreur de sémentique, le nombre d'entrée de la porte "<<
              nom<<" contient un caractère outre qu'un chiffre, ligne "<<nb_ligne<<endl;
              return 1;
            }
            Nand * ptr_obj = new Nand(nom,nb_entry);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"NOR") != string::npos){
            int nb_entry = 0;
            if(conv_int(ligne.substr(ligne.find("[label=\"NOR") + 11,ligne.find("\"];")-ligne.find("[label=\"NOR")-11),&nb_entry)){
              cout<<"\nErreur de sémentique, le nombre d'entrée de la porte "<<
              nom<<" contient un caractère outre qu'un chiffre, ligne "<<nb_ligne<<endl;
              return 1;
            }
            Nor * ptr_obj = new Nor(nom,nb_entry);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"OR") != string::npos){
            int nb_entry = 0;
            if(conv_int(ligne.substr(ligne.find("[label=\"OR") + 10,ligne.find("\"];")-ligne.find("[label=\"OR")-10),&nb_entry)){
              cout<<"\nErreur de sémentique, le nombre d'entrée de la porte "<<
              nom<<" contient un caractère outre qu'un chiffre, ligne "<<nb_ligne<<endl;
              return 1;
            }
            Or * ptr_obj = new Or(nom,nb_entry);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"XNOR") != string::npos){
            int nb_entry = 0;
            if(conv_int(ligne.substr(ligne.find("[label=\"XNOR") + 12,ligne.find("\"];")-ligne.find("[label=\"XNOR")-12),&nb_entry)){
              cout<<"\nErreur de sémentique, le nombre d'entrée de la porte "<<
              nom<<" contient un caractère outre qu'un chiffre, ligne "<<nb_ligne<<endl;
              return 1;
            }
            Xnor * ptr_obj = new Xnor(nom,nb_entry);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"XOR") != string::npos){
            int nb_entry = 0;
            if(conv_int(ligne.substr(ligne.find("[label=\"XOR") + 11,ligne.find("\"];")-ligne.find("[label=\"XOR")-11),&nb_entry)){
              cout<<"\nErreur de sémentique, le nombre d'entrée de la porte "<<
              nom<<" contient un caractère outre qu'un chiffre, ligne "<<nb_ligne<<endl;
              return 1;
            }
            Xor * ptr_obj = new Xor(nom,nb_entry);
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }

          else if(ligne.find("[label=\"MUX") != string::npos){
            ligne = ligne.substr(ligne.find("sel=\"")+5,string::npos);
            string sel_name = ligne.substr(0,ligne.find("\""));
            if(check_name(&sel_name,&v_name_ban)){
              cout<<"Ligne "<<nb_ligne<<endl;
              return 1;
            }

            Gate_mux * ptr_obj = new Gate_mux(nom,2,1);

            ptr_obj->add_sel_name(sel_name);
            ptr_obj->set_is_a_mux(1);

            m_tamp_mux.insert(pair<string,Gate_mux *>(sel_name,ptr_obj));
            //Ajout dans la liste
            v_gate->push_back(ptr_obj);
            v_name_gate.push_back(nom);
          }
        }
      }

      if(flag_seq){
        cout<<"\nInformation, le circuit défini est séquentiel.\n"<<endl;
      }
      else{
        cout<<"\nInformation, le circuit défini est purement combinatoire.\n"<<endl;
      }

      infile.clear();
      infile.seekg(0);
      nb_ligne = 1;

      //Check si au moins 1 entrée, 1 sortie
      if(v_in->size()<1){
        cout<<"\nErreur de déclaration, il n'y a pas d'entrée au circuit."<<endl;
        return 1;
      }
      if(v_out->size()<1){
        cout<<"\nErreur de déclaration, il n'y a pas de sortie au circuit."<<endl;
        return 1;
      }

      ////////////////////////////////////////////////////////////////////////////////
      //CREATION DES ENTRES SORTIE DES GATES
      ////////////////////////////////////////////////////////////////////////////////

      while(getline(infile, ligne)){
        nb_ligne++;
        remove_space(&ligne,&nb_ligne);
        //Si la ligne est un saut de ligne alors passe directement à la ligne suivante
        if(ligne.size() == 0){
        }
        else{
          if(ligne.find("->") != string::npos){
            bool eol = 0; //Flag fin de la ligne
            int index_min = 0; //init index sur le premier nom
            string nom_r_1 = ligne.substr(index_min,ligne.find("->")); //extraction du premier nom a gauche de la fleche
            if(check_name(&nom_r_1,&v_name_ban)){
              cout<<"Ligne "<<nb_ligne<<endl;
              return 1;
            }

            string nom_r_2;
            int type_1 = 0; //init du type du nom avant la fleche
            int type_2 = 0; //init a 0 pour le deuxieme
            if(recherche_type(&type_1,&nom_r_1,v_in,v_out,&v_name_gate)!=0){
              cout<<"\nErreur, nom "<< nom_r_1 <<" non reconnu ligne "<<
              nb_ligne<< endl;
              return 1;
            }

            while(eol == 0){
              index_min += nom_r_1.size() + 2;
              if(recherche_nom_suivant(&eol,&ligne,&index_min,&nom_r_2)!=0){
                cout<<"\nErreur de lecture du fichier .dot, ligne "<< nb_ligne << endl;
                return 1;
              }

              if(check_name(&nom_r_2,&v_name_ban)){
                cout<<"Ligne "<<nb_ligne<<endl;
                return 1;
              }
              if(recherche_type(&type_2,&nom_r_2,v_in,v_out,&v_name_gate)!=0){
                cout<<"\nErreur, nom "<< nom_r_1 <<" non reconnu ligne "<<
                nb_ligne<< endl;
                return 1;
              }

              //Cas ou les deux elements sont des portes
              if(type_1 == 3 && type_2 == 3){
                if(link_double_gate(v_gate,&nom_r_1,&nom_r_2)!=0){
                  cout<<"\nErreur de lecture du fichier .dot, connection entre la porte "<<
                  nom_r_1 <<" et la porte "<< nom_r_2 << " impossible, ligne " <<
                  nb_ligne << endl;
                  return 1;
                }
              }

              //Cas element de gauche est une entre et element de droite une porte
              else if(type_1 == 1 && type_2 == 3){
                if(link_m_input(m_input,v_gate,&nom_r_1,&nom_r_2,&m_tamp_output)!=0){
                  cout<<"\nErreur de lecture du fichier .dot, connection entre l'entrée "<<
                  nom_r_1 <<" et la porte "<< nom_r_2 << " impossible, ligne " <<
                  nb_ligne << endl;
                  return 1;
                }
              }

              //cas ou element de gauche est une porte et element de droite est une sortie
              else if(type_1 == 3 && type_2 == 2){
                if(link_m_tamp_output(&m_tamp_output,v_gate,&nom_r_1,&nom_r_2,v_in)!=0){
                  cout<<"\nErreur de lecture du fichier .dot, connection entre la porte "<<
                  nom_r_1 <<" et la sortie "<< nom_r_2 << " impossible, ligne " <<
                  nb_ligne << endl;
                  return 1;
                }
              }

              //Cas ou element de gauche est une entre et element de droite une sortie
              else if(type_1 == 1 && type_2 == 2){
                cout<<"Attention, l'entrée " << nom_r_1 <<
                " est directement connecté à la sortie "<< nom_r_2 <<", ligne "<<nb_ligne<<endl;

                if(link_m_tamp_output(&m_tamp_output,v_gate,&nom_r_1,&nom_r_2,v_in)!=0){
                  cout<<"\nErreur de lecture du fichier .dot, connection entre l'entrée "<<
                  nom_r_1 <<" et la sortie "<< nom_r_2 << " impossible, ligne " <<
                  nb_ligne << endl;
                  return 1;
                }

                if(link_m_input(m_input,v_gate,&nom_r_1,&nom_r_2,&m_tamp_output)!=0){
                  cout<<"\nErreur de lecture du fichier .dot, connection entre l'entrée "<<
                  nom_r_1 <<" et la sortie "<< nom_r_2 << " impossible, ligne : " <<
                  nb_ligne << endl;
                  return 1;
                }
              }

              //Detection \nErreur si sortie sur une entre ou porte sur entre
              else if(type_2 == 1){
                cout << "\nErreur de d'interconnexion dans la structure du circuit: la sortie "<<
                nom_r_1 <<" est connecté à l'INPUT"<< nom_r_2<<endl;
                cout << "Voir ligne " << nb_ligne << endl;
                return 1;
              }

              nom_r_1 = nom_r_2; //le deuxieme element devient le premier
              type_1 = type_2;

            }
          }
        }
      }

      //Cas particulier des MUX, création des liens avec la selection du Mux
      for(map<string, Gate_mux *>::iterator itr = m_tamp_mux.begin(); itr != m_tamp_mux.end(); itr++){
        int type_1 = 0;
        string nom_r_1 = itr->first;
        string nom_r_2 = itr->second->getName();
        if(recherche_type(&type_1,&nom_r_1,v_in,v_out,&v_name_gate)!=0){
          cout<<"\nErreur, nom "<< nom_r_1 <<" non reconnu ligne "<<
          nb_ligne<< endl;
          return 1;
        }
        if(type_1 == 1){
          if(link_m_input(m_input,v_gate,&nom_r_1,&nom_r_2,&m_tamp_output)!=0){
            cout<<"\nErreur de lecture du fichier .dot, connection entre l'entrée "<<
            nom_r_1 <<" et la porte "<< nom_r_2 << " impossible, ligne : " <<
            nb_ligne << endl;
            return 1;
          }
        }
        if(type_1 == 3){
          if(link_double_gate(v_gate,&nom_r_1,&nom_r_2)!=0){
            cout<<"\nErreur de lecture du fichier .dot, connection entre la porte "<<
            nom_r_1 <<" et la sélection du mux "<< nom_r_2 << " impossible, ligne : " <<
            nb_ligne << endl;
            return 1;
          }
        }
      }

      //Conversion de la map tampon en un vector
      if(change_map_to_vector(&m_tamp_output,v_tamp_output)!=0){
        cout<<"\nErreur de conversion de map à vector pour le vector tampon de sortie "<<endl;
        return 1;
      }

      ////////////////////////////////////////////////////////////////////////////////
      //FIN PROGRAMME
      ////////////////////////////////////////////////////////////////////////////////

      infile.close(); //fermeture fichier .dot

      return 0;
    }
