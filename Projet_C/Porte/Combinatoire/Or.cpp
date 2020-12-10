#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "Or.h"

using namespace std;

int Or::operation(const int & a, const int & b){
  return a || b;
}
