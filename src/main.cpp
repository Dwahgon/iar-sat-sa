#include "cnfsat.h"
#include "simulatedannealing.h"
#include "utils.h"
#include <iostream>
#include <functional>
#include <stdlib.h>

#define N_LITERALS 3

using namespace cnfsat;

int main(int argv, char **argc)
{
  srand(time(NULL));
  Formula f =
      Formula({Clause({Literal(0, false), Literal(1, true)}),
               Clause({Literal(0, true), Literal(1, false), Literal(2, false)}),
               Clause({Literal(0, true)})});
  auto objFunc = std::bind(&Formula::objectiveFunction, &f, std::placeholders::_1);
  auto nFunc = std::bind(&Formula::neighborhoodFunction, &f, std::placeholders::_1);
  SimulatedAnnealing<bool> sa = SimulatedAnnealing<bool>(objFunc, nFunc, coolingSchedule1, 100, 0.1, 100, 100);
  std::vector<bool> initSolution = randomBoolVector(N_LITERALS);

  std::cout << "Formula: " << f << std::endl;
  std::cout << "Initial solution: " << std::endl;
  for (int i = 0; i < N_LITERALS; i++)
    std::cout << "\tx" << i << " = " << initSolution[i] << std::endl;
  std::cout << "Initial solution cost: " << f.objectiveFunction(initSolution) << std::endl;

  std::vector<bool> res = sa.optimize(initSolution);

  std::cout << "Optimized solution: " << std::endl;
  for (int i = 0; i < N_LITERALS; i++)
    std::cout << "\tx" << i << " = " << res[i] << std::endl;
  std::cout << "Optimized solution cost: " << f.objectiveFunction(res) << std::endl;

  return 0;
}