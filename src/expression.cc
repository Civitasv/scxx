#include "expression.h"

#include "call.h"
#include "condition.h"
#include "definition.h"
#include "primitive.h"
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
    case Expression::CALL:
      if (expr.value.call) {
        type = CALL;
        value.call = new Call(*expr.value.call);
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
    case Expression::PRIMITIVE:
      if (expr.value.primitive) {
        type = PRIMITIVE;
        value.primitive = new Primitive(*expr.value.primitive);
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
Expression::Expression(const Condition& condition) : type(CONDITION) {
  value.condition = new Condition(condition);
}
Expression::Expression(const Definition& definition) : type(DEFINITION) {
  value.definition = new Definition(definition);
}
Expression::Expression(const Call& call) : type(CALL) {
  value.call = new Call(call);
}
Expression::Expression(const List& list) : type(LIST) {
  value.list = new List(list);
}
Expression::Expression(const Procedure& procedure) : type(PROCEDURE) {
  value.procedure = new Procedure(procedure);
}
Expression::Expression(const Primitive& primitive) : type(PRIMITIVE) {
  value.primitive = new Primitive(primitive);
}

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
  } else if (type == CALL) {
    if (value.call) {
      delete value.call;
      value.call = nullptr;
    }
  } else if (type == LIST) {
    if (value.list) {
      delete value.list;
      value.list = nullptr;
    }
  } else if (type == PROCEDURE) {
    if (value.procedure) {
      delete value.procedure;
      value.procedure = nullptr;
    }
  } else if (type == PRIMITIVE) {
    if (value.primitive) {
      delete value.primitive;
      value.primitive = nullptr;
    }
  } else if (type == QUOTATION) {
    if (value.quotation) {
      delete value.quotation;
      value.quotation = nullptr;
    }
  } else if (type == CONDITION) {
    if (value.condition) {
      delete value.condition;
      value.condition = nullptr;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
  switch (expr.type) {
    case Expression::SYMBOL:
      os << '"' << *expr.value.symbol << '"';
      break;
    case Expression::NUMBER:
      os << *expr.value.number;
      break;
    case Expression::DEFINITION:
      os << *expr.value.definition;
      break;
    case Expression::QUOTATION:
      os << *expr.value.quotation;
      break;
    case Expression::CONDITION:
      os << *expr.value.condition;
      break;
    case Expression::CALL:
      os << *expr.value.call;
      break;
    case Expression::LIST:
      if (expr.value.list->size() == 0) {
        os << "()";
        break;
      }
      os << "(";
      for (int i = 0; i < expr.value.list->size() - 1; i++) {
        os << expr.value.list->at(i) << " ";
      }
      os << expr.value.list->at(expr.value.list->size() - 1);
      os << ")";
      break;
    case Expression::PRIMITIVE:
      os << *expr.value.primitive;
      break;
    case Expression::PROCEDURE:
      os << *expr.value.procedure;
      break;
    default:
      break;
  }
  return os;
}
}  // namespace scxx
