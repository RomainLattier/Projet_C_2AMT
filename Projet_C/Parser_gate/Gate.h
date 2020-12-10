#ifndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Gate{

private:
  string nom;
  int nb_of_entry;
  int nb_entry_rdy;
  list<bool> input;
  list<Gate*> output;

public:

  Gate(){
    nom = "And_gate_NOT_DEFINED";
    nb_of_entry = 0;
  }

  Gate(string name, int nb = 2, int nb_rdy = 0):nom(name),nb_of_entry(nb),nb_entry_rdy(nb_rdy){}

  ~Gate(){
    cout << "And_gate" << nom << "detruit" << endl;
  }

  int get_nb_entry_rdy(){
    return nb_entry_rdy;
  }

  void add_nb_entry_rdy(){
    nb_entry_rdy ++;
  }

  void add_input(bool in){
    input.push_back(in);
  }

  // void add_output(Gate out){
  //   output.push_back(out);
  // }

  bool operation(bool a, bool b){
    if( a == b )
      return 1;
    else
      return 0;
  }

  // void calc_and_affect(){
  //   if (nb_entry_rdy == nb_of_entry){
  //     bool res = Gate::operation(input[0], input[1]);
  //     if(input.size() > 2){
  //       list<bool>::iterator it_calc = input.begin() + 1;
  //       for (it_calc; it_calc!= input.end(); ++it_calc){
  //         res = Gate::operation(res,*it_calc);
  //       }
  //     }
  //     for(list<Gate>::iterator it_affect = output.begin(); it_affect != output.end(); ++it_affect){
  //         it_affect->input[it_affect.get_nb_entry_rdy()] = res;
  //         it_affect->add_nb_entry_rdy();
  //     }
  //     this->nb_entry_rdy = 0;
  //   }
  // }

};

#endif
