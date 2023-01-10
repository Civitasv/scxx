#pragma once

#include <iostream>
#include <vector>

#include "definition.h"
#include "procedure.h"
#include "quotation.h"
#include "type.h"

namespace scxx {
struct Expression {
  enum Type {
    // Atom
    SYMBOL=-2,
    // 在这里，Token 中的 Symbol 分成了 Symbol 和 Proc
    PROC,
    NUMBER,
    // Spec 中的 List 分为 Special 和 Procedure
    // Special
    DEFINITION,
    QUOTATION,  // quotation 也用在 map 中
    LAMBDA,
    ASSIGNMENT,
    // Primitive and User defined
    PROCEDURE,

    // A general type, 也用在 cons, car, cdr 中
    LIST
  };

  union Value {
    Number* number;
    Symbol* symbol;
    Definition* definition;
    Quotation* quotation;
    Procedure* procedure;
    List* list;
    Proc proc;
  };

  Expression();
  Expression(const Expression& expr);

  // TODO 右值构造器

  ~Expression();

  Expression(Type type);
  Expression(const Symbol& symbol);
  Expression(const Number& number);
  Expression(const Quotation& quotation);
  Expression(const List& list);
  Expression(const Definition& definition);
  Expression(const Procedure& procedure);
  Expression(Proc proc);

  Type type;
  Value value;

  friend std::ostream& operator<<(std::ostream& os, const Expression& expr);
};
}  // namespace scxx
