#ifndef CNF_SAT_H
#define CNF_SAT_H

#include <ostream>
#include <string>
#include <vector>

namespace cnfsat {

class SATComponent {
public:
  virtual bool resolve(const std::vector<bool> &values) = 0;
};

class Literal : SATComponent {
public:
  int i;
  bool negated;
  Literal(int i, bool negated);
  bool resolve(const std::vector<bool> &values);
};

class Clause : SATComponent {
public:
  std::vector<Literal> literals;
  Clause(std::vector<Literal> literals);
  bool resolve(const std::vector<bool> &values);
};

class Formula : SATComponent {
public:
  std::vector<Clause> clauses;
  Formula(std::vector<Clause> clauses);
  bool resolve(const std::vector<bool> &values);
  double objectiveFunction(const std::vector<bool> &values);
  std::vector<bool> neighborhoodFunction(const std::vector<bool> &values);
};

} // namespace cnfsat
std::ostream &operator<<(std::ostream &strm, const cnfsat::Literal &a);
std::ostream &operator<<(std::ostream &strm, const cnfsat::Clause &a);
std::ostream &operator<<(std::ostream &strm, const cnfsat::Formula &a);

#endif