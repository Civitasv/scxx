#include "expression.h"

#include "definition.h"
#include "procedure.h"
#include "quotation.h"
#include "type.h"

namespace scxx {

Expression::Expression() {}

Expression::Expression(const Expression& expr) {
  switch (expr.type) {
    case Expression::SYMBOL:
      if (expr.value.symbol) {
        type = SYMBOL;
        value.symbol = new Symbol(*expr.value.symbol);
      }
      break;
    case Expression::NUMBER:
      if (expr.value.number) {
        type = NUMBER;
        value.number = new Number(*expr.value.number);
      }
      break;
    case Expression::DEFINITION:
      if (expr.value.definition) {
        type = DEFINITION;
        value.definition = new Definition(*expr.value.definition);
      }
      break;
    case Expression::QUOTATION:
      if (expr.value.quotation) {
        type = QUOTATION;
        value.quotation = new Quotation(*expr.value.quotation);
      }
      break;
    case Expression::PROCEDURE:
      if (expr.value.procedure) {
        type = PROCEDURE;
        value.procedure = new Procedure(*expr.value.procedure);
      }
      break;
    case Expression::LIST:
      if (expr.value.list) {
        type = LIST;
        value.list = new List(*expr.value.list);
      }
      break;
    case Expression::PROC:
      if (expr.value.proc) {
        type = PROC;
        value.proc = *expr.value.proc;
      }
      break;
    default:
      break;
  }
}

Expression::Expression(Type type) : type(type) {}
Expression::Expression(const Symbol& symbol) : type(SYMBOL) {
  value.symbol = new Symbol(symbol);
}
Expression::Expression(const Number& number) : type(NUMBER) {
  value.number = new Number(number);
}
Expression::Expression(const Quotation& quotation) : type(QUOTATION) {
  value.quotation = new Quotation(quotation);
}
Expression::Expression(const List& list) : type(LIST) {
  value.list = new List(list);
}
Expression::Expression(const Definition& definition) : type(DEFINITION) {
  value.definition = new Definition(definition);
}
Expression::Expression(const Procedure& procedure) : type(PROCEDURE) {
  value.procedure = new Procedure(procedure);
}

Expression::Expression(Proc proc) : type(PROC) { value.proc = proc; }

Expression::~Expression() {
  if (type == SYMBOL) {
    if (value.symbol) {
      delete value.symbol;
      value.symbol = nullptr;
    }
  } else if (type == NUMBER) {
    if (value.number) {
      delete value.number;
      value.number = nullptr;
    }
  } else if (type == DEFINITION) {
    if (value.definition) {
      delete value.definition;
      value.definition = nullptr;
    }
  } else if (type == PROCEDURE) {
    if (value.procedure) {
      delete value.procedure;
      value.procedure = nullptr;
    }
  } else if (type == QUOTATION) {
    if (value.quotation) {
      delete value.quotation;
      value.quotation = nullptr;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
  switch (expr.type) {
    case Expression::SYMBOL:
      os << "SYMBOL: " << *expr.value.symbol;
      break;
    case Expression::NUMBER:
      os << "NUMBER: " << *expr.value.number;
      break;
    case Expression::DEFINITION:
      os << *expr.value.definition;
      break;
    case Expression::QUOTATION:
      os << *expr.value.quotation;
      break;
    case Expression::PROCEDURE:
      os << *expr.value.procedure;
      break;
    case Expression::LIST:
      os << "[";
      for (auto& item : *expr.value.list) {
        os << item << " ";
      }
      os << "]";
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
