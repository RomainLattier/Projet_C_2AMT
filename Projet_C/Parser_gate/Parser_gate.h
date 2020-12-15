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
#include "../Porte/Gate_out.h"

using namespace std;

bool check_open_file(const ifstream * infile);
bool check_ext_path_dot(const string * s_path);
bool recherche_type(int *type,const string *nom_r,const vector<string> *v_in, const vector<string> *v_out, const vector<string> *v_gate);
bool recherche_v(const string *nom_r,const vector<string> *v_base);
bool recherche_nom_suivant(bool * eol,const string * ligne,int * index_min, string *nom);
bool link_m_input( map<string, vector<Gate*>* > *m_input, vector<Gate*> *v_gate,const string *nom_r1,const string *nom_r2, const map<string, Gate*> *m_tamp_output);
bool link_m_tamp_output(map<string, Gate*> *m_tamp_output,vector<Gate*> *v_gate,const string *nom_r_1,const string *nom_r_2,const vector<string> * v_in);
bool change_map_to_vector(map<string,Gate*>* m_gate,vector<Gate*>* v_gate);

int parser_gate(map<string,vector<Gate *>* > *m_input,map<string,vector<int>* > *m_output,vector<Gate *> *v_gate, vector<Gate*> *v_tamp_output,vector<string> *v_int,vector<string> *v_out,const string * s_path);
#endif
