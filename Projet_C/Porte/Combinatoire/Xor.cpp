#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "Xor.h"

using namespace std;

int Xor::operation(const int & a, const int & b){
  return a ^ b;
}
