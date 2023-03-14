#include "expression.h"

#include <fmt/core.h>

#include <sstream>
#include <utility>

#include "call.h"
#include "condition.h"
#include "definition.h"
#include "primitive.h"
#include "procedure.h"
#include "quotation.h"
#include "type.h"

namespace scxx {
Expression::Expression() : type(NONE) {}

Expression::Expression(const Expression& expr) { InitializeLValue(expr); }

Expression::Expression(Expression&& expr) { InitializeRValue(std::move(expr)); }

Expression::Expression(Type type) : type(type) {}
Expression::Expression(const Symbol& symbol) : type(SYMBOL), value(symbol) {}

Expression::Expression(const Number& number) : type(NUMBER), value(number) {}

Expression::Expression(const Quotation& quotation)
    : type(QUOTATION), value(quotation) {}

Expression::Expression(const Condition& condition)
    : type(CONDITION), value(condition) {}

Expression::Expression(const Definition& definition)
    : type(DEFINITION), value(definition) {}

Expression::Expression(const Call& call) : type(CALL), value(call) {}

Expression::Expression(const List& list) : type(LIST), value(list) {}

Expression::Expression(const Procedure& procedure)
    : type(PROCEDURE), value(procedure) {}

Expression::Expression(const Primitive& primitive)
    : type(PRIMITIVE), value(primitive) {}

Expression::Expression(Symbol&& symbol)
    : type(SYMBOL), value(std::move(symbol)) {}

Expression::Expression(Number&& number)
    : type(NUMBER), value(std::move(number)) {}

Expression::Expression(Quotation&& quotation)
    : type(QUOTATION), value(std::move(quotation)) {}

Expression::Expression(Condition&& condition)
    : type(CONDITION), value(std::move(condition)) {}

Expression::Expression(Definition&& definition)
    : type(DEFINITION), value(std::move(definition)) {}

Expression::Expression(Call&& call) : type(CALL), value(std::move(call)) {}

Expression::Expression(List&& list) : type(LIST), value(std::move(list)) {}

Expression::Expression(Procedure&& procedure)
    : type(PROCEDURE), value(std::move(procedure)) {}

Expression::Expression(Primitive&& primitive)
    : type(PRIMITIVE), value(std::move(primitive)) {}

Expression& Expression::operator=(const Expression& expr) {
  InitializeLValue(expr);
  return *this;
}

Expression& Expression::operator=(Expression&& expr) {
  InitializeRValue(std::move(expr));
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
  switch (expr.type) {
    case Expression::SYMBOL:
    case Expression::NUMBER:
    case Expression::DEFINITION:
    case Expression::QUOTATION:
    case Expression::CONDITION:
    case Expression::CALL:
    case Expression::PRIMITIVE:
    case Expression::PROCEDURE:
    case Expression::LAMBDA:
      std::visit([&os](auto&& arg) { os << arg; }, expr.value);
      break;
    case Expression::LIST: {
      const List& list = std::get<List>(expr.value);
      if (list.size() == 0) {
        os << "()";
        break;
      }
      os << "(";
      for (int i = 0; i < list.size() - 1; i++) {
        os << list[i] << " ";
      }
      os << list[list.size() - 1];
      os << ")";
    } break;

    default:
      break;
  }
  return os;
}

std::string Expression::Dump() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

void Expression::InitializeLValue(const Expression& expr) {
  using namespace std;
  switch (expr.type) {
    case Expression::NUMBER:
      if (const Number* v = get_if<Number>(&expr.value)) {
        type = NUMBER;
        value = *v;
      }
      break;
    case Expression::SYMBOL:
      if (const Symbol* v = get_if<Symbol>(&expr.value)) {
        type = SYMBOL;
        value = *v;
      }
      break;
    case Expression::QUOTATION:
      if (const Quotation* v = get_if<Quotation>(&expr.value)) {
        type = QUOTATION;
        value = *v;
      }
      break;
    case Expression::CONDITION:
      if (const Condition* v = get_if<Condition>(&expr.value)) {
        type = CONDITION;
        value = *v;
      }
      break;
    case Expression::DEFINITION:
      if (const Definition* v = get_if<Definition>(&expr.value)) {
        type = DEFINITION;
        value = *v;
      }
      break;
    case Expression::CALL:
      if (const Call* v = get_if<Call>(&expr.value)) {
        type = CALL;
        value = *v;
      }
      break;
    case Expression::PRIMITIVE:
      if (const Primitive* v = get_if<Primitive>(&expr.value)) {
        type = PRIMITIVE;
        value = *v;
      }
      break;
    case Expression::PROCEDURE:
      if (const Procedure* v = get_if<Procedure>(&expr.value)) {
        type = PROCEDURE;
        value = *v;
      }
      break;
    case Expression::LIST:
      if (const List* v = get_if<List>(&expr.value)) {
        type = LIST;
        value = *v;
      }
      break;
    default:
      break;
  }
}

void Expression::InitializeRValue(Expression&& expr) {
  using namespace std;
  switch (expr.type) {
    case Expression::NUMBER:
      if (Number* v = get_if<Number>(&expr.value)) {
        type = NUMBER;
        value = std::move(*v);
      }
      break;
    case Expression::SYMBOL:
      if (Symbol* v = get_if<Symbol>(&expr.value)) {
        type = SYMBOL;
        value = std::move(*v);
      }
      break;
    case Expression::QUOTATION:
      if (Quotation* v = get_if<Quotation>(&expr.value)) {
        type = QUOTATION;
        value = std::move(*v);
      }
      break;
    case Expression::CONDITION:
      if (Condition* v = get_if<Condition>(&expr.value)) {
        type = CONDITION;
        value = std::move(*v);
      }
      break;
    case Expression::DEFINITION:
      if (Definition* v = get_if<Definition>(&expr.value)) {
        type = DEFINITION;
        value = std::move(*v);
      }
      break;
    case Expression::CALL:
      if (Call* v = get_if<Call>(&expr.value)) {
        type = CALL;
        value = std::move(*v);
      }
      break;
    case Expression::PRIMITIVE:
      if (Primitive* v = get_if<Primitive>(&expr.value)) {
        type = PRIMITIVE;
        value = std::move(*v);
      }
      break;
    case Expression::PROCEDURE:
      if (Procedure* v = get_if<Procedure>(&expr.value)) {
        type = PROCEDURE;
        value = std::move(*v);
      }
      break;
    case Expression::LIST:
      if (List* v = get_if<List>(&expr.value)) {
        type = LIST;
        value = std::move(*v);
      }
      break;
    default:
      break;
  }
}

llvm::Value* Expression::CodeGen() {
  using namespace std;
  using namespace llvm;
  using LLVMType = llvm::Type;

  switch (type) {
    // case Expression::NUMBER: {
    //   auto number = AsNumber();
    //   return ConstantFP::get(*the_context, APFloat(*number));
    // }
    // case Expression::SYMBOL: {
    //   auto symbol = AsSymbol();
    //   // NOTE: Maybe I need environment model?
    //   Value* v = named_values[*symbol];
    //   if (!v) {
    //     LogErrorV("Unknown symbol");
    //   }
    //   return v;
    // }
    // case Expression::QUOTATION: {
    //   break;
    // }
    // case Expression::CONDITION: {
    //   break;
    // }
    // case Expression::DEFINITION: {
    //   auto definition = AsDefinition();
    //   // 1. retrieve the variable
    //   auto variable = definition->variable.get();
    //   // 2. retrieve the value
    //   auto value = definition->value->CodeGen();
    //
    //   // 3. add into named_values
    //   named_values[*variable] = value;
    // }
    // case Expression::CALL: {
    //   auto call = AsCall();
    //
    //   // 1. the function
    //   Expression* proc = call->proc.get();
    //   if (proc->type == SYMBOL) {
    //   } else if (proc->type == PROCEDURE) {
    //     // lambda
    //   }
    //   const Expression& expr = proc->type == Expression::SYMBOL
    //                                ? env->Find(*proc->AsSymbol())
    //                                : *proc->AsProcedure();
    //
    //   if (expr.type == Expression::NONE) {
    //     panic(fmt::format("cannot find procedure: {}", expr.Dump()));
    //   }
    //   // 2. the args
    //   List args;
    //   for (auto& item : *call->args) {
    //     args.push_back(Eval(item, env));
    //   }
    //
    //   if (expr.type == Expression::PROCEDURE) {
    //     auto body = expr.AsProcedure()->body.get();
    //     auto params = expr.AsProcedure()->params.get();
    //     Environment this_env(*params, args, env);
    //     for (int i = 0; i < body->size() - 1; i++) {
    //       Eval(body->at(i), &this_env);
    //     }
    //     return Eval(body->at(body->size() - 1), &this_env);
    //   } else if (expr.type == Expression::PRIMITIVE) {
    //     Proc proc = expr.AsPrimitive()->proc;
    //     return proc(args);
    //   }
    //   break;
    // }
    // case Expression::PRIMITIVE: {
    //   break;
    // }
    // case Expression::PROCEDURE: {
    //   auto procedure = AsProcedure();
    //   vector<LLVMType*> doubles(procedure->params->size(),
    //                             llvm::Type::getDoubleTy(*the_context));
    //   FunctionType* FT =
    //   FunctionType::get(LLVMType::getDoubleTy(*the_context),
    //                                        doubles, false);
    //
    //   Function* F = Function::Create(FT, Function::ExternalLinkage, Name,
    //                                  the_module.get());
    //
    //   // Set names for all arguments.
    //   unsigned Idx = 0;
    //   for (auto& Arg : F->args()) Arg.setName(Args[Idx++]);
    //   break;
    // }
    // case Expression::LIST: {
    //   break;
    // }
    // default: {
    //   break;
    // }
  }
}
}  // namespace scxx
