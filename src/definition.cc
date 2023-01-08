#include "definition.h"

#include "expression.h"

namespace scxx {
Definition::Definition(Symbol* variable, Expression* value)
    : variable(variable), value(value) {}

std::ostream& operator<<(std::ostream& os, const Definition& definition) {
  os << "define: " << *definition.variable << " ";
  os << *definition.value;
  return os;
}

Definition::~Definition() {
  if (variable) delete variable;
  if (value) delete value;
}
}  // namespace scxx
