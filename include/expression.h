#pragma once

#include <iostream>
#include <vector>

#include "definition.h"
#include "procedure.h"
#include "type.h"

namespace scxx {
struct Expression {
  enum Type {
    // Atom
    SYMBOL,
    NUMBER,
    // Special
    DEFINITION,
    // Primitive and User defined
    PROCEDURE,
    PROC,
    LIST
  };
  union Value {
    Number* number;
    Symbol* symbol;
    Definition* definition;
    List* list;
    Procedure* procedure;
    Proc proc;
  };

  Expression();

  Expression(Type type);
  Expression(Symbol* symbol);
  Expression(Number* number);
  Expression(List* list);
  Expression(Definition* definition);
  Expression(Procedure* procedure);
  Expression(Proc proc);

  ~Expression();

  Type type;
  Value value;

  friend std::ostream& operator<<(std::ostream& os, const Expression& exp);
};
}  // namespace scxx
