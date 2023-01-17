#include "eval.h"

#include "environment.h"
#include "error.h"
#include "fmt/core.h"
#include "predicate.h"
#include "type.h"

namespace scxx {
Expression Eval(const Expression& expr, Environment* env) {
  if (expr.type == Expression::NUMBER) {
    // just just return it
    return expr;
  } else if (expr.type == Expression::SYMBOL) {
    auto result = env->Find(*expr.AsSymbol());
    if (result.type == Expression::NONE) {
      panic(fmt::format("cannot find symbol: {}", expr.Dump()));
    }
    return result;
  } else if (expr.type == Expression::CONDITION) {
    Expression predicate = Eval(*expr.AsCondition()->predicate, env);
    if (IsTrue(&predicate)) {
      return Eval(*expr.AsCondition()->consequent, env);
    } else {
      return Eval(*expr.AsCondition()->alternative, env);
    }
  } else if (expr.type == Expression::DEFINITION) {
    // 1. retrieve the variable
    auto variable = expr.AsDefinition()->variable.get();

    // 2. retrieve the value
    Expression value = Eval((*expr.AsDefinition()->value), env);

    env->Insert(*variable, value);
    return *variable;
  } else if (expr.type == Expression::QUOTATION) {
    return *expr.AsQuotation()->quotes;
  } else if (expr.type == Expression::PROCEDURE) {
    Procedure* proc = expr.AsProcedure();
    proc->env = env;
    return *proc;
  } else if (expr.type == Expression::CALL) {
    Call* call = expr.AsCall();
    // 1. the function
    Expression* proc = call->proc.get();
    const Expression& expr = proc->type == Expression::SYMBOL
                                 ? env->Find(*proc->AsSymbol())
                                 : *proc->AsProcedure();

    if (expr.type == Expression::NONE) {
      panic(fmt::format("cannot find procedure: {}", expr.Dump()));
    }
    // 2. the args
    List args;
    for (auto& item : *call->args) {
      args.push_back(Eval(item, env));
    }

    if (expr.type == Expression::PROCEDURE) {
      auto body = expr.AsProcedure()->body.get();
      auto params = expr.AsProcedure()->params.get();
      Environment this_env(*params, args, env);
      for (int i = 0; i < body->size() - 1; i++) {
        Eval(body->at(i), &this_env);
      }
      return Eval(body->at(body->size() - 1), &this_env);
    } else if (expr.type == Expression::PRIMITIVE) {
      Proc proc = expr.AsPrimitive()->proc;
      return proc(args);
    }
  }
  return {};
}
}  // namespace scxx

// (map square '(1 2 3))
// => ((square 1) (square 2) (square 3))
