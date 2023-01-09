#include "eval.h"

namespace scxx {
Expression* Eval(Expression* expr, scxx::Environment* env) {
  if (expr->type == Expression::NUMBER) {
    // just just return it
    return expr;
  } else if (expr->type == Expression::SYMBOL) {
    return env->Find(*expr->value.symbol);
  } else if (expr->type == Expression::DEFINITION) {
    // 1. retrieve the variable
    Symbol* variable = expr->value.definition->variable;

    // 2. retrieve the value
    Expression* value = expr->value.definition->value;

    env->Insert(*variable, value);
  } else if (expr->type == Expression::PROCEDURE) {
    Procedure* procedure = expr->value.procedure;

    // 1. the function
    Expression* proc = Eval(procedure->proc, env);

    // 2. the args
    std::vector<Expression*> args;
    for (auto& item : procedure->args) {
      args.push_back(Eval(item, env));
    }

    return proc->value.proc(args);
  }
  return nullptr;
}
}  // namespace scxx
