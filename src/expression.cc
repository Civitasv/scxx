#include "expression.h"

#include "procedure.h"

namespace scxx {

Expression::Expression() {}

Expression::Expression(Type type) : type(type) {}
Expression::Expression(Symbol* symbol) : type(SYMBOL) { value.symbol = symbol; }
Expression::Expression(Number* number) : type(NUMBER) { value.number = number; }
Expression::Expression(List* list) : type(LIST) { value.list = list; }
Expression::Expression(Definition* definition) : type(DEFINITION) {
  value.definition = definition;
}
Expression::Expression(Procedure* procedure) : type(PROCEDURE) {
  value.procedure = procedure;
}

Expression::Expression(Proc proc) : type(PROC) { value.proc = proc; }

Expression::~Expression() {
  if (type == SYMBOL) {
    if (value.symbol) delete value.symbol;
  } else if (type == NUMBER) {
    if (value.number) delete value.number;
  } else if (type == DEFINITION) {
    if (value.definition) delete value.definition;
  } else if (type == PROCEDURE) {
    if (value.procedure) delete value.procedure;
  }
}

std::ostream& operator<<(std::ostream& os, const Expression& exp) {
  switch (exp.type) {
    case Expression::SYMBOL:
      os << *exp.value.symbol;
      break;
    case Expression::NUMBER:
      os << *exp.value.number;
      break;
    case Expression::DEFINITION:
      os << *exp.value.definition;
      break;
    case Expression::PROCEDURE:
      os << *exp.value.procedure;
      break;
    case Expression::PROC:
      os << "PROC";
      break;
    default:
      break;
  }
  return os;
}
}  // namespace scxx
