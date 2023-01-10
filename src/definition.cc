#include "definition.h"

#include "expression.h"

namespace scxx {
Definition::Definition(const Symbol& variable, const Expression& value)
    : variable(new Symbol(variable)), value(new Expression(value)) {}

Definition::Definition(const Definition& definition) {
  variable = new Symbol(*definition.variable);
  value = new Expression(
      *definition.value);  // I even cannot invoke Definition constructor from
                           // this copy constructor, what a weird choice.
}

std::ostream& operator<<(std::ostream& os, const Definition& definition) {
  os << "define: " << *definition.variable << " ";
  os << *definition.value;
  return os;
}

Definition::~Definition() {
  if (variable) {
    delete variable;
    variable = nullptr;
  }
  if (value) {
    delete value;
    value = nullptr;
  }
}
}  // namespace scxx
