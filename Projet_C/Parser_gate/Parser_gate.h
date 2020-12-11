#ifndef _PARSER_GATE_H_
#define _PARSER_GATE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "../Porte/Combinatoire/And.h"
#include "../Porte/Combinatoire/Inv.h"
#include "../Porte/Combinatoire/Nand.h"
#include "../Porte/Combinatoire/Nor.h"
#include "../Porte/Combinatoire/Or.h"
#include "../Porte/Combinatoire/Xnor.h"
#include "../Porte/Combinatoire/Xor.h"


bool recherche_type(int *type,const string *nom_r,const vector<string> *v_in, const vector<string> *v_out, const vector<string> *v_gate);
bool recherche_v(const string *nom_r,const vector<string> *v_base);
bool recherche_nom_suivant(bool * eol,const string * ligne,int * index_min, string *nom);

int parser_gate(map<string,vector<Gate *>* > *m_input,map<string,vector<int>* > *m_output,vector<Gate *> *v_gate, map<string, Gate*> *m_tamp_output,vector<string> *v_int,vector<string> *v_out, char * path);
#endif
