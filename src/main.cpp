#include "cnfsat.h"
#include "simulatedannealing.h"
#include "utils.h"
#include <iostream>
#include <functional>

#define N_LITERALS 3

using namespace cnfsat;

int main(int argv, char **argc)
{
  Formula f =
      Formula({Clause({Literal(0, false), Literal(1, true)}),
               Clause({Literal(0, true), Literal(1, false), Literal(2, false)}),
               Clause({Literal(0, true)})});
  auto objFunc = std::bind(&Formula::objectiveFunction, &f, std::placeholders::_1);
  auto nFunc = std::bind(&Formula::neighborhoodFunction, &f, std::placeholders::_1);
  std::vector<bool> initSolution = randomBoolVector(N_LITERALS);

  std::cout << "Formula: " << f << std::endl;
  std::cout << "Initial solution: " << std::endl;
  for (int i = 0; i < N_LITERALS; i++)
    std::cout << "\tx" << i << " = " << initSolution[i] << std::endl;
  std::cout << "Initial solution cost: " << f.objectiveFunction(initSolution) << std::endl;

  std::vector<bool> res = sa<bool>(objFunc, nFunc, 0.5, 1000, 50.0, initSolution);

  std::cout << "Optimized solution: " << std::endl;
  for (int i = 0; i < N_LITERALS; i++)
    std::cout << "\tx" << i << " = " << res[i] << std::endl;
  std::cout << "Optimized solution cost: " << f.objectiveFunction(res) << std::endl;

  return 0;
}