#pragma once

#include <iostream>
#include <vector>

#include "call.h"
#include "condition.h"
#include "definition.h"
#include "primitive.h"
#include "procedure.h"
#include "quotation.h"
#include "type.h"

namespace scxx {
struct Expression {
  enum Type {
    /** Atom */
    SYMBOL,
    NUMBER,
    /** ------------- */

    /** Special */
    DEFINITION,
    QUOTATION,  // quotation 也用在 map 中
    LAMBDA,
    CONDITION,
    /** ------------- */

    /** Function call */
    CALL,
    // Primitive
    PRIMITIVE,
    // User defined
    PROCEDURE,
    /** ------------- */

    /** Mid */
    LIST,  // A general type, 也用在 cons, car, cdr 中
    /** ------------- */
  };

  union Value {
    Number* number;
    Symbol* symbol;

    Definition* definition;
    Quotation* quotation;
    Condition* condition;

    Call* call;
    Procedure* procedure;
    Primitive* primitive;

    List* list;
  };

  Expression();
  Expression(const Expression& expr);

  // TODO 右值构造器

  ~Expression();

  Expression(Type type);
  Expression(const Symbol& symbol);
  Expression(const Number& number);
  Expression(const Quotation& quotation);
  Expression(const Condition& condition);
  Expression(const Definition& definition);
  Expression(const Call& call);
  Expression(const Primitive& primitive);
  Expression(const Procedure& procedure);
  Expression(const List& list);

  Type type;
  Value value;

  friend std::ostream& operator<<(std::ostream& os, const Expression& expr);
  std::string Dump();
};
}  // namespace scxx
