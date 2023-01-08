#include "eval.h"

namespace scxx {
Expression* Eval(Expression* expr, scxx::Environment* env) {
  if (expr->type == Expression::NUMBER) {
    // just just return it
    return expr;
  } else if (expr->type == Expression::SYMBOL) {
    return env->Find(expr->value.symbol);
  } else if (expr->type == Expression::DEFINITION) {
  }
  return nullptr;
}
}  // namespace scxx
