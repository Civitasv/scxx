#pragma once

#include <vector>

#include "environment.h"
#include "expression.h"

namespace scxx {
// +
Expression* Add(std::vector<Expression*> exprs);
Expression* Minus(std::vector<Expression*> exprs);
Expression* Product(std::vector<Expression*> exprs);
Expression* Divide(std::vector<Expression*> exprs);

Expression* Quote(std::vector<Expression*> exprs);
Expression* Gt(std::vector<Expression*> exprs);
Expression* Lt(std::vector<Expression*> exprs);
Expression* Ge(std::vector<Expression*> exprs);
Expression* Le(std::vector<Expression*> exprs);
Expression* Eq(std::vector<Expression*> exprs);
Expression* Abs(std::vector<Expression*> exprs);
Expression* Cons(std::vector<Expression*> exprs);
Expression* Car(std::vector<Expression*> exprs);
Expression* Cdr(std::vector<Expression*> exprs);
Expression* SameAddress(std::vector<Expression*> exprs);
Expression* Max(std::vector<Expression*> exprs);
Expression* Min(std::vector<Expression*> exprs);
Expression* Map(std::vector<Expression*> exprs);
Expression* IsNumber(std::vector<Expression*> exprs);
Expression* IsProcedure(std::vector<Expression*> exprs);

Environment* StandardEnv();
}  // namespace scxx
