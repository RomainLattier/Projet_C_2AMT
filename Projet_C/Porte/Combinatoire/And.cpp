#include <iostream>
#include <string.h>
#include <vector>

#include "../Gate.h"
#include "../Gate_comb.h"
#include "And.h"

using namespace std;

int And::operation(const int & a, const int & b){
  return a && b;
}
