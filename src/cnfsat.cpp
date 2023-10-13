#include "cnfsat.h"
#include <ostream>
#include <random>
#include <vector>

using namespace cnfsat;

Clause::Clause(const std::vector<int> &ls) : literals(ls) {}

bool Clause::resolve(const std::vector<bool> &values)
{
  for (auto l : this->literals)
  {
    auto v = values[abs(l) - 1];
    if (v == (l > 0))
      return true;
  }
  return false;
}

Formula::Formula(const std::vector<Clause> &clauses, unsigned int n) : nVars(n)
{
  this->clauses = clauses;
}

bool Formula::resolve(const std::vector<bool> &values)
{
  bool res = true;
  for (auto iter = this->clauses.begin(); iter < this->clauses.end(); iter++)
  {
    res = res && iter->resolve(values);
  }
  return res;
}

double Formula::objectiveFunction(const std::vector<bool> &values)
{
  double res = 0.0;
  for (auto iter = this->clauses.begin(); iter < this->clauses.end(); iter++)
  {
    res += 1.0 * (double)(!iter->resolve(values));
  }
  return res;
}

std::vector<bool> Formula::neighborhoodFunction(const std::vector<bool> &values)
{
  std::vector<bool> res = values;
  std::size_t i, size = res.size();
  for (i = 0; i < size; i++)
  {
    if (0.5 > (float)rand() / (float)RAND_MAX)
      res[i] = !res[i];
  }
  return res;
}

std::ostream &operator<<(std::ostream &strm, const Clause &a)
{
  strm << '(';
  for (auto it = a.literals.begin(); it < a.literals.end(); it++)
  {
    if (it != a.literals.begin())
      strm << " | ";
    strm << (*it < 0 ? "!" : "") << 'x' << abs(*it);
  }
  strm << ')';
  return strm;
}

std::ostream &operator<<(std::ostream &strm, const Formula &a)
{
  for (auto iter = a.clauses.begin(); iter < a.clauses.end(); iter++)
  {
    if (iter != a.clauses.begin())
      strm << " & ";
    strm << *iter;
  }
  return strm;
}

Formula &operator<<(Formula &f, const Clause &c)
{
  f.clauses.push_back(c);
  return f;
}

Clause &operator<<(Clause &c, const int i)
{
  c.literals.push_back(i);
  return c;
}