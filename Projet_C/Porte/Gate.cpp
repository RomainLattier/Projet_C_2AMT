#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"

using namespace std;

void Gate::update_input(int res){
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
