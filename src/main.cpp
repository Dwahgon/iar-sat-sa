#include "cnfsat.h"
#include "simulatedannealing.h"
#include "randsearch.h"
#include "utils.h"
#include "dimacscnfparser.h"
#include "parseargs.h"
#include <iostream>
#include <ostream>
#include <sstream>
#include <functional>
#include <stdlib.h>
#include <string>
#include <random>

using namespace cnfsat;
using namespace opt;

void configureArgParser(ArgumentsParser &argParser)
{
  argParser.addArgument({"coolingScheduleIndex", 'i', "cooling-schedule-i", "Which cooling schedule will be used. Values 0-9 are accepted", false, "0"});
  argParser.addArgument({"T0", 'z', "t0", "Initial temperature", false, "100"});
  argParser.addArgument({"TN", 'f', "tn", "Final temperature", false, "0.01"});
  argParser.addArgument({"SAmax", 's', "samax", "Iterations between each temperature cooldown", false, "10"});
  argParser.addArgument({"N", 'n', "", "Number of temperature cooldown iterations", false, "100"});
}

int main(int argv, char **argc)
{
  ArgumentsParser args;
  std::random_device r;
  configureArgParser(args);
  args.parseArgs(argv, argc);

  srand(r());

  Formula f = parseDimacsCnfFormula(std::cin);
  auto objFunc = std::bind(&Formula::objectiveFunction, &f, std::placeholders::_1);
  auto nFunc = std::bind(&Formula::neighborhoodFunction, &f, std::placeholders::_1);
  auto randFunc = std::bind(randomBoolVector, (std::size_t)f.nVars);
  coolingSchedule c;
  switch (std::stoi(args["coolingScheduleIndex"]))
  {
  case 0:
    c = coolingSchedule0;
    break;
  case 1:
    c = coolingSchedule1;
    break;
  case 2:
    c = coolingSchedule2;
    break;
  case 3:
    c = coolingSchedule3;
    break;
  case 4:
    c = coolingSchedule4;
    break;
  case 5:
    c = coolingSchedule5;
    break;
  case 6:
    c = coolingSchedule6;
    break;
  case 7:
    c = coolingSchedule7;
    break;
  case 8:
    c = coolingSchedule8;
    break;
  case 9:
    c = coolingSchedule9;
    break;
  default:
    break;
  }
  std::stringstream saOs, rsOs;
  SimulatedAnnealing<bool> sa = SimulatedAnnealing<bool>(objFunc, nFunc, c, std::stod(args["T0"]), std::stod(args["TN"]), std::stoi(args["SAmax"]), std::stoi(args["N"]));
  RandomSearch<bool> rs = RandomSearch<bool>(objFunc, randFunc, std::stoi(args["N"]));
  std::vector<bool> initSolution = randomBoolVector(f.nVars);

  // std::cout << "Formula: " << f << std::endl;
  // std::cout << "Initial solution: " << std::endl
  //           << "\t";
  // for (std::size_t i = 0; i < initSolution.size(); i++)
  //   std::cout << "x" << i << " = " << initSolution[i] << "; ";
  // std::cout << "\nInitial solution cost: " << f.objectiveFunction(initSolution) << std::endl;

  std::vector<bool> saRes = sa.optimize(initSolution, saOs);
  std::vector<bool> rsRes = rs.optimize(initSolution, rsOs);

  std::cout << "sa_cost,sa_temp,rs,,sa_final_cost,rs_final_cost\n";
  std::string saOut, rsOut;
  bool printFinalCost = true;
  while (saOs >> saOut && rsOs >> rsOut)
  {
    std::cout << saOut << "," << rsOut;

    if (printFinalCost)
    {
      printFinalCost = false;
      std::cout << ",," << objFunc(saRes) << "," << objFunc(rsRes);
    }
    std::cout << std::endl;
  }
  // std::cout << "Optimized solution: " << std::endl
  //           << "\t";
  // for (std::size_t i = 0; i < res.size(); i++)
  //   std::cout << "x" << i << " = " << res[i] << "; ";
  // std::cout << "Simulated Annealing solution cost: " << f.objectiveFunction(saRes) << std::endl;
  // std::cout << "Random Search solution cost: " << f.objectiveFunction(rsRes) << std::endl;

  return 0;
}