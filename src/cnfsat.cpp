#include "cnfsat.h"
#include <ostream>
#include <random>
#include <vector>

using namespace cnfsat;

Literal::Literal(int i, bool negated)
{
  this->i = i;
  this->negated = negated;
}

bool Literal::resolve(const std::vector<bool> &values)
{
  return (values[this->i] && !this->negated) ||
         (!values[this->i] && this->negated);
}

Clause::Clause(std::vector<Literal> literals) { this->literals = literals; }

bool Clause::resolve(const std::vector<bool> &values)
{
  for (auto iter = this->literals.begin(); iter < this->literals.end();
       iter++)
  {
    if (iter->resolve(values))
      return true;
  }
  return false;
}

Formula::Formula(std::vector<Clause> clauses) { this->clauses = clauses; }

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

std::ostream &operator<<(std::ostream &strm, const Literal &a)
{
  if (a.negated)
    strm << '!';
  return strm << 'x' << a.i;
}

std::ostream &operator<<(std::ostream &strm, const Clause &a)
{
  strm << '(';
  for (auto iter = a.literals.begin(); iter < a.literals.end(); iter++)
  {
    if (iter != a.literals.begin())
      strm << " | ";
    strm << *iter;
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