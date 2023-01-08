#pragma once

#include <iostream>
#include <vector>

#include "definition.h"
#include "type.h"

namespace scxx {
typedef std::vector<Expression*> List;
typedef Expression* (*Proc)(std::vector<Expression*>);

struct Expression {
  enum Type { SYMBOL, NUMBER, PROC, DEFINITION, LIST };
  union Value {
    Number* number;
    Symbol* symbol;
    Definition* definition;
    List* list;
    Proc proc;
  };

  Expression();

  Expression(Type type);
  Expression(Symbol* symbol);
  Expression(Number* number);
  Expression(List* list);
  Expression(Definition* definition);
  Expression(Proc proc);

  ~Expression();

  Type type;
  Value value;

  friend std::ostream& operator<<(std::ostream& os, const Expression& exp);
};
}  // namespace scxx
