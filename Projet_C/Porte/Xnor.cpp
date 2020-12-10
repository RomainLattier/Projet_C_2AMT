#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "Xnor.h"

using namespace std;

int Xnor::operation(const int & a, const int & b){
  return !(a ^ b);
}
