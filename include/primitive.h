#pragma once

#include <vector>

#include "environment.h"
#include "expression.h"

namespace scxx {
// +
Expression Add(const List& exprs);
Expression Minus(const List& exprs);
Expression Product(const List& exprs);
Expression Divide(const List& exprs);

Expression Quote(const List& exprs);
Expression Gt(const List& exprs);
Expression Lt(const List& exprs);
Expression Ge(const List& exprs);
Expression Le(const List& exprs);
Expression Eq(const List& exprs);
Expression Abs(const List& exprs);
Expression Cons(const List& exprs);
Expression Car(const List& exprs);
Expression Cdr(const List& exprs);
Expression SameAddress(const List& exprs);
Expression Max(const List& exprs);
Expression Min(const List& exprs);
Expression Map(const List& exprs);
Expression IsNumber(const List& exprs);
Expression IsProcedure(const List& exprs);

Environment* StandardEnv();
}  // namespace scxx
