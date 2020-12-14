#ifndef _PARSER_STIMULI_H_
#define _PARSER_STIMULI_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;


bool verif_nom_exist(const string * nom,const vector<string> *v_in);
bool verif_delta(const vector<string> *v_in, const map<string,vector<int>*> *m_tamp, const int * nb);

int parser_stimuli(const vector<string> *v_in, vector<int> *v_delta,map<string,vector<int>* > *m_stimuli,const char * path);

#endif
