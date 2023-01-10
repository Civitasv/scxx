#include "condition.h"

#include "expression.h"

namespace scxx {
Condition::Condition(const Expression& predicate, const Expression& consequent,
                     const Expression& alternative)
    : predicate(new Expression(predicate)),
      consequent(new Expression(consequent)),
      alternative(new Expression(alternative)) {}

Condition::Condition(const Condition& If) {
  predicate = new Expression(*If.predicate);
  consequent = new Expression(*If.consequent);
  alternative = new Expression(*If.alternative);
}

std::ostream& operator<<(std::ostream& os, const Condition& If) {
  os << "if: " << *If.predicate << " ";
  os << "then: " << *If.consequent << " ";
  os << "else: " << *If.alternative;
  return os;
}

Condition::~Condition() {
  if (predicate) {
    delete predicate;
    predicate = nullptr;
  }
  if (alternative) {
    delete alternative;
    alternative = nullptr;
  }
  if (consequent) {
    delete consequent;
    consequent = nullptr;
  }
}
}  // namespace scxx
