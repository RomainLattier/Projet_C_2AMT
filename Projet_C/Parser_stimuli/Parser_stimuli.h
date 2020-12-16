#ifndef _PARSER_STIMULI_H_
#define _PARSER_STIMULI_H_

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <stdlib.h>

#include "../Parser_gate/Parser_gate.h"

using namespace std;

bool check_ext_path_json(const string * s_path);
bool verif_syntaxe(ifstream * infile);
bool find_vector(const vector<string> * vector,const string * nom);
bool verif_nom_input(ifstream * infile,const vector<string> *v_in);
bool verif_delta(const vector<string> *v_in, const map<string,vector<int>*> *m_tamp, const int * nb);

int parser_stimuli(const vector<string> *v_in, vector<int> *v_delta,map<string,vector<int>* > *m_stimuli,const string * s_path);

#endif
