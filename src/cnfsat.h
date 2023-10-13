#ifndef CNF_SAT_H
#define CNF_SAT_H

#include <ostream>
#include <string>
#include <vector>

namespace cnfsat
{

  class SATComponent
  {
  public:
    virtual bool resolve(const std::vector<bool> &values) = 0;
  };

  class Clause : SATComponent
  {
  public:
    std::vector<int> literals;
    Clause(const std::vector<int> &literals);
    bool resolve(const std::vector<bool> &values);
  };

  class Formula : SATComponent
  {
  public:
    const unsigned int nVars;
    std::vector<Clause> clauses;
    Formula(const std::vector<Clause> &clauses, unsigned int n);
    bool resolve(const std::vector<bool> &values);
    double objectiveFunction(const std::vector<bool> &values);
    std::vector<bool> neighborhoodFunction(const std::vector<bool> &values);
  };

} // namespace cnfsat
std::ostream &operator<<(std::ostream &strm, const cnfsat::Clause &a);
std::ostream &operator<<(std::ostream &strm, const cnfsat::Formula &a);
cnfsat::Formula &operator<<(cnfsat::Formula &f, const cnfsat::Clause &c);
cnfsat::Clause &operator<<(cnfsat::Clause &f, const int &c);

#endif