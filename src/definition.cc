#include "definition.h"

#include "expression.h"

namespace scxx {
Definition::Definition(const Symbol& variable, const Expression& value)
    : variable(std::make_unique<Symbol>(variable)),
      value(std::make_unique<Expression>(value)) {}

Definition::Definition(Symbol&& variable, Expression&& value)
    : variable(std::make_unique<Symbol>(std::move(variable))),
      value(std::make_unique<Expression>(std::move(value))) {}

Definition::Definition(const Definition& definition)
    : variable(std::make_unique<Symbol>(*definition.variable)),
      value(std::make_unique<Expression>(*definition.value)) {}

Definition::Definition(Definition&& definition)
    : variable(std::move(definition.variable)),
      value(std::move(definition.value)) {}

Definition& Definition::operator=(const Definition& definition) {
  variable = std::make_unique<Symbol>(*definition.variable);
  value = std::make_unique<Expression>(*definition.value);
  return *this;
}

Definition& Definition::operator=(Definition&& definition) {
  variable = std::move(definition.variable);
  value = std::move(definition.value);
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Definition& definition) {
  os << "define: " << *definition.variable << " ";
  os << *definition.value;
  return os;
}
}  // namespace scxx
