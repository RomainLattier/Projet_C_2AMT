#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "Inv.h"

using namespace std;

int Inv::operation(const int & a, const int & b = 0){
  return !a;
}
