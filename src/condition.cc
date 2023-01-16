#include "condition.h"

#include "expression.h"

namespace scxx {
Condition::Condition(const Expression& predicate, const Expression& consequent,
                     const Expression& alternative)
    : predicate(std::make_unique<Expression>(predicate)),
      consequent(std::make_unique<Expression>(consequent)),
      alternative(std::make_unique<Expression>(alternative)) {}

Condition::Condition(Expression&& predicate, Expression&& consequent,
                     Expression&& alternative)
    : predicate(std::make_unique<Expression>(std::move(predicate))),
      consequent(std::make_unique<Expression>(std::move(consequent))),
      alternative(std::make_unique<Expression>(std::move(alternative))) {}

Condition::Condition(const Condition& If)
    : predicate(std::make_unique<Expression>(*If.predicate)),
      consequent(std::make_unique<Expression>(*If.consequent)),
      alternative(std::make_unique<Expression>(*If.alternative)) {}

Condition::Condition(Condition&& condition)
    : predicate(std::move(condition.predicate)),
      consequent(std::move(condition.consequent)),
      alternative(std::move(condition.alternative)) {}

Condition& Condition::operator=(const Condition& condition) {
  predicate = std::make_unique<Expression>(*condition.predicate);
  consequent = std::make_unique<Expression>(*condition.consequent);
  alternative = std::make_unique<Expression>(*condition.alternative);
  return *this;
}

Condition& Condition::operator=(Condition&& condition) {
  predicate = std::move(condition.predicate);
  consequent = std::move(condition.consequent);
  alternative = std::move(condition.alternative);
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Condition& If) {
  os << "if: " << *If.predicate << " ";
  os << "then: " << *If.consequent << " ";
  os << "else: " << *If.alternative;
  return os;
}
}  // namespace scxx
