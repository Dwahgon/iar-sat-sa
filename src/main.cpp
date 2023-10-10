#include "cnfsat.h"
#include <iostream>

using namespace cnfsat;

int main(int argv, char **argc) {
  bool values[3] = {false, true, false};
  Formula f =
      Formula({Clause({Literal(0, false), Literal(1, true)}),
               Clause({Literal(0, true), Literal(1, false), Literal(2, false)}),
               Clause({Literal(0, true)})});
  std::cout << f << '\n';
  std::cout << f.resolve(values) << '\n';
  return 0;
}