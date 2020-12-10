#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "And.h"

using namespace std;

int And::operation(const int & a, const int & b){
  if( a == b )
    return 1;
  else
    return 0;
}
