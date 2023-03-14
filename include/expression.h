#pragma once

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <cstddef>
#include <iostream>
#include <map>
#include <variant>
#include <vector>

#include "call.h"
#include "condition.h"
#include "definition.h"
#include "error.h"
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
    Number, 
    Symbol,
    Definition, 
    Quotation,
    Condition, 
    Call,
    Procedure, 
    Primitive,
    List
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

  Symbol* AsSymbol() {
    if (Symbol* v = std::get_if<Symbol>(&value)) {
      return v;
    }
    return nullptr;
  }

  Number* AsNumber() {
    if (Number* v = std::get_if<Number>(&value)) {
      return v;
    }
    return nullptr;
  }

  Quotation* AsQuotation() {
    if (Quotation* v = std::get_if<Quotation>(&value)) {
      return v;
    }
    return nullptr;
  }

  Condition* AsCondition() {
    if (Condition* v = std::get_if<Condition>(&value)) {
      return v;
    }
    return nullptr;
  }

  Definition* AsDefinition() {
    if (Definition* v = std::get_if<Definition>(&value)) {
      return v;
    }
    return nullptr;
  }

  Call* AsCall() {
    if (Call* v = std::get_if<Call>(&value)) {
      return v;
    }
    return nullptr;
  }

  Primitive* AsPrimitive() {
    if (Primitive* v = std::get_if<Primitive>(&value)) {
      return v;
    }
    return nullptr;
  }

  Procedure* AsProcedure() {
    if (Procedure* v = std::get_if<Procedure>(&value)) {
      return v;
    }
    return nullptr;
  }

  List* AsList() {
    if (List* v = std::get_if<List>(&value)) {
      return v;
    }
    return nullptr;
  }

  friend std::ostream& operator<<(std::ostream& os, const Expression& expr);
  std::string Dump() const;

  // For llvm IR generation
  llvm::Value* CodeGen();
  llvm::Value* LogErrorV(const std::string& str) {
    scxx::panic(str);
    return nullptr;
  }

 private:
  void InitializeLValue(const Expression& expr);
  void InitializeRValue(Expression&& expr);

 private:
  // for llvm IR generation
  std::unique_ptr<llvm::LLVMContext>
      the_context;  ///< contains a lot of core LLVM data structures
  std::unique_ptr<llvm::IRBuilder<>>
      builder;  ///< helper project that makes it easy to generate LLVM
                ///< instructions.
  std::unique_ptr<llvm::Module>
      the_module;  ///< contains functions and global variables.
  std::map<std::string, llvm::Value*>
      named_values;  ///< keeps track of which values are defined in the current
                     ///< scope and what their LLVM representation is.
};
}  // namespace scxx
