#ifndef _PARSER_GATE_H_
#define _PARSER_GATE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "../Porte/Combinatoire/And.h"

int parser_gate(map<string,list<Gate *> > *m_input,map<string,vector<bool> > *m_output,list<Gate *> *l_gate, vector<string> *l_gate_avaible);

#endif
