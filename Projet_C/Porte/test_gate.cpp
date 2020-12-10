#include <iostream>
#include <string.h>
#include <vector>

#include "Gate.h"
#include "Gate_comb.h"
#include "And.h"

using namespace std;

int main(){

  And A1("And4_1",4);
  And A2("And2_2",2);

  A1.add_input(1);
  A1.add_input(1);
  A1.add_input(1);
  A1.add_input(1);

  A2.add_input(0);
  A2.add_input(0);

  A1.add_output(&A2);

  A1.print_input_value();
  A1.print_output_name();

  A1.setNbRdy(3);

  //A1.calc_and_affect();

  A2.print_input_value();

  return 0;
}
