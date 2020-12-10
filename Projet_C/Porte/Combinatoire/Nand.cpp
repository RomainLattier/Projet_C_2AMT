#include <iostream>
#include <string.h>
#include <vector>

#include "../Gate.h"
#include "../Gate_comb.h"
#include "Nand.h"

using namespace std;

int Nand::operation(const int & a, const int & b){
  return !(a && b);
}
