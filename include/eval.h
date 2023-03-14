#pragma once
#include <string>

#include "environment.h"
#include "expression.h"

namespace scxx {
Expression Eval(Expression& expr, Environment* env);
}  // namespace scxx
