#include "eval.h"

#include "type.h"

namespace scxx {
Expression Eval(const Expression& expr, Environment& env) {
  if (expr.type == Expression::NUMBER) {
    // just just return it
    return expr;
  } else if (expr.type == Expression::SYMBOL) {
    return env.Find(*expr.value.symbol);
  } else if (expr.type == Expression::DEFINITION) {
    // 1. retrieve the variable
    Symbol* variable = expr.value.definition->variable;

    // 2. retrieve the value
    Expression value = Eval((*expr.value.definition->value), env);

    env.Insert(*variable, value);
    return *variable;
  } else if (expr.type == Expression::QUOTATION) {
    return *expr.value.quotation->quotes;
  } else if (expr.type == Expression::PROCEDURE) {
    Procedure* procedure = expr.value.procedure;
    // 1. the function
    Symbol* proc_name = procedure->proc_name;
    const Expression& proc = env.Find(*proc_name);

    // 2. the args
    List args;
    for (auto& item : *procedure->args) {
      args.push_back(Eval(item, env));
    }

    return proc.value.proc(args);
  }
  return nullptr;
}
}  // namespace scxx
