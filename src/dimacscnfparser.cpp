#include <sstream>
#include <string>
#include <istream>
#include <vector>
#include "cnfsat.h"

cnfsat::Formula parseDimacsCnfFormula(std::istream &is)
{
    std::string l;
    unsigned int nVars;
    std::string word;
    std::vector<int> literals;
    std::vector<cnfsat::Clause> clauses;
    while (std::getline(is, l))
    {
        if (l[0] == 'c')
            continue;
        else if (l[0] == 'p')
        {
            std::istringstream(l) >> word >> word >> word;
            nVars = std::stoul(word);
        }
        else if (l[0] == '%')
            break;
        else
        {
            std::istringstream iss(l);
            while (iss >> word && word != "0")
            {
                literals.push_back(std::stoi(word));
            }
            clauses.push_back(cnfsat::Clause(literals));
            literals.clear();
        }
    }
    return cnfsat::Formula(clauses, nVars);
}