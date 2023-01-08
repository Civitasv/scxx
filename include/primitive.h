#pragma once

#include <vector>

#include "environment.h"
#include "expression.h"
#include "type.h"

namespace scxx {
inline Expression* Add(std::vector<Expression*> exprs) {
  double d = 0.0;
  for (auto& expr : exprs) {
    d += *(expr->value.number);
  }
  return new Expression(new Number(d));
}

inline Environment* StandardEnv() {
  Environment* env = new Environment();

  env->Insert(new Symbol("+"), new Expression(Add));

  return env;
}
}  // namespace scxx
