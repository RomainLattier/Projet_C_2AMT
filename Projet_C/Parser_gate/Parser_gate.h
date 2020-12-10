#ifndef _PARSER_GATE_H_
#define _PARSER_GATE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "../Porte/Combinatoire/And.h"

int parser_gate(map<string,list<Gate *> > *m_input,map<string,vector<int> > *m_output,vector<Gate *> *v_gate, vector<Gate*> *v_tamp_output);

#endif
