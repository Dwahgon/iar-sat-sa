#include "cnfsat.h"
#include <ostream>
#include <vector>

using namespace cnfsat;

Literal::Literal(int i, bool negated) {
  this->i = i;
  this->negated = negated;
}

bool Literal::resolve(bool *values) {
  return (values[this->i] && !this->negated) ||
         (!values[this->i] && this->negated);
}

Clause::Clause(std::vector<Literal> literals) { this->literals = literals; }

bool Clause::resolve(bool *values) {
  bool res = false;
  for (auto iter = this->literals.begin(); iter < this->literals.end();
       iter++) {
    res = res || iter->resolve(values);
  }
  return res;
}

Formula::Formula(std::vector<Clause> clauses) { this->clauses = clauses; }

bool Formula::resolve(bool *values) {
  bool res = true;
  for (auto iter = this->clauses.begin(); iter < this->clauses.end(); iter++) {
    res = res && iter->resolve(values);
  }
  return res;
}

std::ostream &operator<<(std::ostream &strm, const Literal &a) {
  if (a.negated)
    strm << '!';
  return strm << 'x' << a.i;
}

std::ostream &operator<<(std::ostream &strm, const Clause &a) {
  strm << '(';
  for (auto iter = a.literals.begin(); iter < a.literals.end(); iter++) {
    if (iter != a.literals.begin())
      strm << " | ";
    strm << *iter;
  }
  strm << ')';
  return strm;
}

std::ostream &operator<<(std::ostream &strm, const Formula &a) {
  for (auto iter = a.clauses.begin(); iter < a.clauses.end(); iter++) {
    if (iter != a.clauses.begin())
      strm << " & ";
    strm << *iter;
  }
  return strm;
}