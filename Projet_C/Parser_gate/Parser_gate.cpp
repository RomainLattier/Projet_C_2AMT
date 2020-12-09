#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

int parser_gate(map<string,Gate *> *ptr_m_input,map<string,vector<bool> *> *ptr_m_output,list<string> *ptr_l_gate) {

  ////////////////////////////////////////////////////////////////////////////////
  //pour test a donner en entrer
  ////////////////////////////////////////////////////////////////////////////////
  // string tab_test[3];
  // tab_test[0]="\"XOR2\"";
  // tab_test[1]="\"AND2\"";
  // tab_test[2]="\"OR2\"";
  //
  // int nb_gate = sizeof(tab_test)/sizeof(tab_test[0]);
  //  cout << nb_gate<<endl;

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  ifstream infile;
  infile.open("Test_lecture.dot", fstream::in); //ouverture du fichier .dot en mode lecture

  ////////////////////////////////////////////////////////////////////////////////
  //VARIABLES
  ////////////////////////////////////////////////////////////////////////////////

  // int taille_input =0;
  // int taille_output =0;
  // int taille_gate = 0;
  // int i_input = 0;
  // int i_output = 0;
  // int i_gate = 0;
  // int nb_carac = 0;
  string ligne; //lecture ligne par ligne
  list<string> l_tamp_int;
  list<string> l_tamp_out;

  ////////////////////////////////////////////////////////////////////////////////
  //Recherche du nombre d'elements dans les listes
  ////////////////////////////////////////////////////////////////////////////////
  // while(getline(infile, ligne)){
  //   if(ligne.find("\"INPUT\"") != string::npos){
  //     taille_input ++;
  //   }
  //   else if(ligne.find("\"OUTPUT\"") != string::npos){
  //     taille_output ++;
  //   }
  //   else{
  //     for(string *ptr = tab_test; ptr<tab_test + nb_gate; ptr++){
  //       if(ligne.find(*ptr) != string::npos){
  //         taille_gate ++;
  //       }
  //     }
  //   }
  //   //    cout<<infile.tellg()<<endl;
  // }

  //controle
  // cout <<"nb input = " << taille_input<<endl;
  // cout <<"nb output = " << taille_output<<endl;
  // cout <<"nb gate = " << taille_gate<<endl;

  ////////////////////////////////////////////////////////////////////////////////
  //CREATION TABLEAU
  ////////////////////////////////////////////////////////////////////////////////
  //
  // string *tab_INPUT = new string[taille_input];
  // string *tab_OUTPUT = new string[taille_output];
  // string *tab_GATE = new string[taille_gate];
  // tab_INPUT[taille_input] = NULL;
  //
  // infile.clear();
  // infile.seekg(0);

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

//Remplissage map

  while(getline(infile, ligne)){
    //    cout << ligne << endl;
    if(ligne.find("\"INPUT\"") != string::npos){
      tab_INPUT[i_input] = ligne.substr(0,ligne.find(" "));

      nb_carac = infile.tellg();
      //      cout << "ok_input" << endl;
    }
    else if(ligne.find("\"OUTPUT\"") != string::npos){
      tab_OUTPUT[i_output] = ligne.substr(0,ligne.find(" "));

      nb_carac = infile.tellg();
      //      cout << "ok_output" << endl;
    }
    else{
      for(string *ptr = tab_test; ptr<tab_test + nb_gate; ptr++){ //recherche parmi les gate dispo 
        if(ligne.find(*ptr) != string::npos){
          tab_GATE[i_gate] = ligne.substr(0,ligne.find(" "));



          nb_carac = infile.tellg();
          //        cout << "ok_gate" << endl;
        }
      }
    }
  }

  // cout << nb_carac<<endl;

  ////////////////////////////////////////////////////////////////////////////////
  //Affichage controle tableau des types
  ////////////////////////////////////////////////////////////////////////////////

  // cout << "Affichage tab_input"<<endl;
  // for(int i = 0; i < taille_input;i++){
  //   cout << tab_INPUT[i] <<endl;
  // }
  //
  // cout << "Affichage tab_output"<<endl;
  // for(int i = 0; i < taille_output;i++){
  //   cout << tab_OUTPUT[i] <<endl;
  // }
  //
  // cout << "Affichage tab_gate"<<endl;
  // for(int i = 0; i < taille_gate;i++){
  //   cout << tab_GATE[i] <<endl;
  // }

  //   while(getline(infile, ligne)){
  // //    cout << ligne << endl;
  //
  //   }


  ////////////////////////////////////////////////////////////////////////////////
  //CREATION DES ENTRES SORTIE DES GATES
  ////////////////////////////////////////////////////////////////////////////////

  // infile.clear();
  // infile.seekg(nb_carac);
  //
  // while(getline(infile, ligne)){
  //   //    cout << ligne << endl;
  //   if(ligne.find("\"INPUT\"") != string::npos){
  //
  //
  //   }
  //   else if(ligne.find("\"OUTPUT\"") != string::npos){
  //
  //
  //   }
  //   else{
  //     for(string *ptr = tab_test; ptr<tab_test + nb_gate; ptr++){
  //       if(ligne.find(*ptr) != string::npos){
  //       }
  //     }
  //   }
  // }

  ////////////////////////////////////////////////////////////////////////////////
  //FIN PROGRAMME LECTURE, A MODIFIER
  ////////////////////////////////////////////////////////////////////////////////

  infile.close(); //fermeture fichier .dot

  //A DEPLACER DANS LE PRG MAIN
  // delete [] tab_INPUT;
  // delete [] tab_OUTPUT;
  // delete [] tab_GATE;


  //  cout << "FIN PRG"<<endl;
  return 0;
}
