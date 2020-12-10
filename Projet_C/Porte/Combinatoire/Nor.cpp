#include <iostream>
#include <string.h>
#include <vector>

#include "../Gate.h"
#include "../Gate_comb.h"
#include "Nor.h"

using namespace std;

int Nor::operation(const int & a, const int & b){
  return !(a || b);
}
