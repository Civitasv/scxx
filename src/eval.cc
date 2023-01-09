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
    Expression* value = Eval(expr->value.definition->value, env);

    env->Insert(*variable, value);
    return new Expression(variable);
  } else if (expr->type == Expression::PROCEDURE) {
    Procedure* procedure = expr->value.procedure;

    // 1. the function
    Symbol* proc_name = procedure->proc_name;
    Expression* proc = env->Find(*proc_name);

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
