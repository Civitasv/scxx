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
    /** None */
    NONE,
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
  } type;

  // clang-format off
  std::variant<
    std::unique_ptr<Number>, 
    std::unique_ptr<Symbol>,
    std::unique_ptr<Definition>, 
    std::unique_ptr<Quotation>,
    std::unique_ptr<Condition>, 
    std::unique_ptr<Call>,
    std::unique_ptr<Procedure>, 
    std::unique_ptr<Primitive>,
    std::unique_ptr<List>
  > value;
  // clang-format on

  Expression();
  Expression(const Expression& expr);

  Expression(Expression&& expr);

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

  Expression(Symbol&& symbol);
  Expression(Number&& number);
  Expression(Quotation&& quotation);
  Expression(Condition&& condition);
  Expression(Definition&& definition);
  Expression(Call&& call);
  Expression(Primitive&& primitive);
  Expression(Procedure&& procedure);
  Expression(List&& list);

  Expression& operator=(const Expression& expr);
  Expression& operator=(Expression&& expr);

  Symbol* AsSymbol() const {
    if (const std::unique_ptr<Symbol>* v =
            std::get_if<std::unique_ptr<Symbol>>(&value)) {
      return v->get();
    }
    return nullptr;
  }

  Number* AsNumber() const {
    if (const std::unique_ptr<Number>* v =
            std::get_if<std::unique_ptr<Number>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  Quotation* AsQuotation() const {
    if (const std::unique_ptr<Quotation>* v =
            std::get_if<std::unique_ptr<Quotation>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  Condition* AsCondition() const {
    if (const std::unique_ptr<Condition>* v =
            std::get_if<std::unique_ptr<Condition>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  Definition* AsDefinition() const {
    if (const std::unique_ptr<Definition>* v =
            std::get_if<std::unique_ptr<Definition>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  Call* AsCall() const {
    if (const std::unique_ptr<Call>* v =
            std::get_if<std::unique_ptr<Call>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  Primitive* AsPrimitive() const {
    if (const std::unique_ptr<Primitive>* v =
            std::get_if<std::unique_ptr<Primitive>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  Procedure* AsProcedure() const {
    if (const std::unique_ptr<Procedure>* v =
            std::get_if<std::unique_ptr<Procedure>>(&value)) {
      return v->get();
    }
    return nullptr;
  }
  List* AsList() const {
    if (const std::unique_ptr<List>* v =
            std::get_if<std::unique_ptr<List>>(&value)) {
      return v->get();
    }
    return nullptr;
  }

  friend std::ostream& operator<<(std::ostream& os, const Expression& expr);
  std::string Dump() const;

 private:
  void InitializeLValue(const Expression& expr);
  void InitializeRValue(Expression&& expr);
};
}  // namespace scxx
