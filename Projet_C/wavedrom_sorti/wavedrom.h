#ifndef _WAVEDROM_H_
#define _WAVEDROM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

bool verif_open_file(const ofstream * infile);

int count_wave(const vector<int> *v_duree_delta);
bool fill_wave(const vector<int> *v_duree_delta,const vector<string> *v_name,const map<string,vector<int>* > *m_val,ofstream * infile, const int * nb_wave);

int wavedrom_output(const vector<string> *v_input,const vector<string> * v_output,const vector<int> *v_duree_delta,const map<string,vector<int>* > *m_stimulis,const map<string,vector<int>* > *m_output,const char * path);

#endif
