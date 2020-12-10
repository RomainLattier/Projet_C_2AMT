#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

int parser_gate(map<string,Gate *> *ptr_m_input,map<string,vector<bool> *> *ptr_m_output,list<string> *ptr_l_gate) {

  ////////////////////////////////////////////////////////////////////////////////
  //OUVERTURE FICHIER
  ////////////////////////////////////////////////////////////////////////////////

  ifstream infile;
  infile.open("Test_lecture.dot", fstream::in); //ouverture du fichier .dot en mode lecture

  ////////////////////////////////////////////////////////////////////////////////
  //VARIABLES
  ////////////////////////////////////////////////////////////////////////////////

  string ligne; //lecture ligne par ligne
  list<string> l_tamp_int;
  list<string> l_tamp_out;

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
