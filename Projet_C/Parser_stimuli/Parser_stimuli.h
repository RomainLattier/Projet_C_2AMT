#ifndef _PARSER_STIMULI_H_
#define _PARSER_STIMULI_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

int parser_stimuli(vector<string> *v_int, vector<int> *v_delta,map<string,vector<int> > *m_stimuli, char * path);

#endif
