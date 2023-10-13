#include "cnfsat.h"
#include "simulatedannealing.h"
#include "utils.h"
#include "dimacscnfparser.h"
#include <iostream>
#include <functional>
#include <stdlib.h>

using namespace cnfsat;

int main(int argv, char **argc)
{
  srand(time(NULL));
  Formula f = parseDimacsCnfFormula(std::cin);
  auto objFunc = std::bind(&Formula::objectiveFunction, &f, std::placeholders::_1);
  auto nFunc = std::bind(&Formula::neighborhoodFunction, &f, std::placeholders::_1);
  SimulatedAnnealing<bool> sa = SimulatedAnnealing<bool>(objFunc, nFunc, coolingSchedule1, 100, 0.1, 100, 100);
  std::vector<bool> initSolution = randomBoolVector(f.nVars);

  std::cout << "Formula: " << f << std::endl;
  std::cout << "Initial solution: " << std::endl
            << "\t";
  for (std::size_t i = 0; i < initSolution.size(); i++)
    std::cout << "x" << i << " = " << initSolution[i] << "; ";
  std::cout << "\nInitial solution cost: " << f.objectiveFunction(initSolution) << std::endl;

  std::vector<bool> res = sa.optimize(initSolution);

  std::cout << "Optimized solution: " << std::endl
            << "\t";
  for (std::size_t i = 0; i < res.size(); i++)
    std::cout << "x" << i << " = " << res[i] << "; ";
  std::cout << "\nOptimized solution cost: " << f.objectiveFunction(res) << std::endl;

  return 0;
}