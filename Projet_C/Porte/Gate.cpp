#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

void Gate::update_input(int res){
  // cout << "entree ready" <<this->get_nb_entry_rdy();
  this->input[this->get_nb_entry_rdy()] = res;
  this->add_nb_entry_rdy();
}

void Gate::print_input_value(){
  for (unsigned i = 0; i < this->input.size(); i++){
    cout << this->input.at(i) << endl;
  }
}

void Gate::print_output_name(){
  for (unsigned i = 0; i < this->output.size(); i++){
    cout << this->output.at(i)->getName() << endl;
  }
}

int Gate::is_stable(){
  // cout << "this->nb_entry_rdy " << this->nb_entry_rdy <<endl;
  // cout << "this->nb_of_entry " << this->nb_of_entry <<endl;
  // cout << "this->nb_entry_rdy >= this->nb_of_entry" << (this->nb_entry_rdy >= this->nb_of_entry) <<endl;
  return this->nb_entry_rdy >= this->nb_of_entry;
}

int Gate::getValueAndReset(){
  this->nb_entry_rdy = 0;
  return this->input.at(0);
}

int Gate::getValueOutput(){
  this->nb_entry_rdy == 0;
  return this->input.at(0);
}

bool Gate::rebouclage(string ante){
  bool rebouclage = 0;
  for(unsigned i = 0; i<this->antescedant.size(); i++){
    if(this->antescedant.at(i) == ante){
      rebouclage = 1;
    }
  }
  return rebouclage;
}

void Gate::add_antescedant(string ante){
  // cout <<"add_antescedant" << endl;
  bool ante_existe = 0;
  if(this->antescedant.size() == 0){
    this->antescedant.push_back(ante);
    // cout << "antescedant vide" << endl;
  }
  else{
    for(unsigned i = 0; i<this->antescedant.size(); i++){
      // cout << "i" << i <<endl;
      if(this->antescedant.at(i) == ante){
        ante_existe = 1;
      }
    }
    if(!ante_existe){
      this->antescedant.push_back(ante);
    }
  }
  // cout << "fin add antescedant" << endl;
}
