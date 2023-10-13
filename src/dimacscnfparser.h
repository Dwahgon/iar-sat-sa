#ifndef DIMACS_CNF_PARSER_H
#define DIMACS_CNF_PARSER_H

#include <string>
#include <istream>
#include "cnfsat.h"

cnfsat::Formula parseDimacsCnfFormula(std::istream &is);

#endif