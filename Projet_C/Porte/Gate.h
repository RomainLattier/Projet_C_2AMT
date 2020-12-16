#ifndef _GATE_H
#define _GATE_H

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Gate{

protected:
  string nom;
  int nb_of_entry;
  int nb_entry_rdy;
  vector<int> input;
  vector<Gate*> output;
  //Attribut special mux;
  int is_a_mux;
  vector<string> sel_name; //Nom des entre de sel le 1er dans le vector est le 1er à gauche sur la ligne
  vector<string> gate_input; //Nom des entre de gate le 1er dans le vector est le 1er recontrer dans le fichier
  vector<int> sel_value; //Stocke les valeurs des sel

public:

  Gate(string G_name, int G_nb_of_entry):nom(G_name),nb_of_entry(G_nb_of_entry){
    nb_entry_rdy = 0;
    is_a_mux = 0;
    for(int i = 0; i<nb_of_entry;i++){
      input.push_back(0);
    }
  };

  virtual ~Gate(){};

  int get_is_a_mux(){
    return is_a_mux;
  }

  void set_is_a_mux(const int &val){
    is_a_mux = val;
  }

  int get_nb_of_entry(){
    return nb_of_entry;
  }

  int get_nb_entry_rdy(){
    return nb_entry_rdy;
  }

  string getName(){
    return nom;
  }

  void add_nb_entry_rdy(){
    nb_entry_rdy ++;
  }

  void add_input(int in){
    input.push_back(in);
  }

  void add_output(Gate * out){
    output.push_back(out);
  }

  void setNbRdy(int n){
    nb_entry_rdy = n;
  }

  void print_output_name();

  void print_input_value();

  void update_input(int res); //fonction qui permet d'update la liste d'input

  int is_stable();

  int getValueAndReset();

  int getValueOutput();

  void add_sel_name(string s){
    sel_name.push_back(s);
  }

  string get_sel_name(int i){
    return sel_name.at(i);
  }

  void add_gate_input(string s){
    gate_input.push_back(s);
  }

  virtual void calc_and_affect() = 0;

  virtual void update_mux(int n, string s) = 0;

};

#endif
