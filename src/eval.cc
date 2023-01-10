#include "eval.h"

#include "environment.h"
#include "predicate.h"
#include "type.h"

namespace scxx {
Expression Eval(const Expression& expr, Environment* env) {
  if (expr.type == Expression::NUMBER) {
    // just just return it
    return expr;
  } else if (expr.type == Expression::SYMBOL) {
    return env->Find(*expr.value.symbol);
  } else if (expr.type == Expression::CONDITION) {
    Expression predicate = Eval(*expr.value.condition->predicate, env);
    if (IsTrue(&predicate)) {
      return Eval(*expr.value.condition->consequent, env);
    } else {
      return Eval(*expr.value.condition->alternative, env);
    }
  } else if (expr.type == Expression::DEFINITION) {
    // 1. retrieve the variable
    Symbol* variable = expr.value.definition->variable;

    // 2. retrieve the value
    Expression value = Eval((*expr.value.definition->value), env);

    env->Insert(*variable, value);
    return *variable;
  } else if (expr.type == Expression::QUOTATION) {
    return *expr.value.quotation->quotes;
  } else if (expr.type == Expression::PROCEDURE) {
    Procedure* proc = expr.value.procedure;
    proc->env = env;
    return *proc;
  } else if (expr.type == Expression::CALL) {
    Call* call = expr.value.call;
    // 1. the function
    Symbol* proc_name = call->proc_name;
    const Expression& expr = env->Find(*proc_name);

    // 2. the args
    List args;
    for (auto& item : *call->args) {
      args.push_back(Eval(item, env));
    }

    if (expr.type == Expression::PROCEDURE) {
      List* body = expr.value.procedure->body;
      std::vector<Symbol>* params = expr.value.procedure->params;
      Environment this_env(*params, args, env);
      for (int i = 0; i < body->size() - 1; i++) {
        Eval(body->at(i), &this_env);
      }
      return Eval(body->at(body->size() - 1), &this_env);
    } else if (expr.type == Expression::PRIMITIVE) {
      Proc proc = expr.value.primitive->proc;
      return proc(args);
    }
  }
  return {};
}
}  // namespace scxx

// (map square '(1 2 3))
// => ((square 1) (square 2) (square 3))
