#include "primitive.h"

#include "type.h"

namespace scxx {
Expression* Add(std::vector<Expression*> exprs) {
  double d = 0.0;
  for (auto& expr : exprs) {
    d += *(expr->value.number);
  }
  return new Expression(new Number(d));
}

Expression* Minus(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    d -= *(expr->value.number);
  }
  return new Expression(new Number(d));
}

Expression* Product(std::vector<Expression*> exprs) {
  double d = 1.0;
  for (auto& expr : exprs) {
    d *= *(expr->value.number);
  }
  return new Expression(new Number(d));
}

Expression* Divide(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    d /= *(expr->value.number);
  }
  return new Expression(new Number(d));
}

Expression* Gt(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (d <= *(expr->value.number)) return new Expression(new Symbol("#f"));
  }
  return new Expression(new Symbol("#t"));
}

Expression* Lt(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (d >= *(expr->value.number)) return new Expression(new Symbol("#f"));
  }
  return new Expression(new Symbol("#t"));
}

Expression* Ge(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (d < *(expr->value.number)) return new Expression(new Symbol("#f"));
  }
  return new Expression(new Symbol("#t"));
}

Expression* Le(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (d > *(expr->value.number)) return new Expression(new Symbol("#f"));
  }
  return new Expression(new Symbol("#t"));
}

Expression* Eq(std::vector<Expression*> exprs) {
  double d = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (d != *(expr->value.number)) return new Expression(new Symbol("#f"));
  }
  return new Expression(new Symbol("#t"));
}

Expression* Abs(std::vector<Expression*> exprs) {
  double d = std::abs(*(exprs[0]->value.number));
  return new Expression(new Number(d));
}

Expression* Cons(std::vector<Expression*> exprs) {
  return new Expression(new List({exprs[0], exprs[1]}));
}

Expression* Car(std::vector<Expression*> exprs) {
  return (*exprs[0]->value.list)[0];
}

Expression* Cdr(std::vector<Expression*> exprs) {
  return (*exprs[0]->value.list)[1];
}

Expression* SameAddress(std::vector<Expression*> exprs) {
  return new Expression(new Symbol(exprs[0] == exprs[1] ? "#t" : "#f"));
}

Expression* Max(std::vector<Expression*> exprs) {
  double max = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (max < *(expr->value.number)) max = *(expr->value.number);
  }
  return new Expression(new Number(max));
}

Expression* Min(std::vector<Expression*> exprs) {
  double min = *(exprs[0]->value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression* expr = exprs[i];
    if (min > *(expr->value.number)) min = *(expr->value.number);
  }
  return new Expression(new Number(min));
}

Expression* Map(std::vector<Expression*> exprs) {
  Proc f = exprs[0]->value.proc;
  List* list = exprs[1]->value.list;

  Expression* res = new Expression(Expression::LIST);

  for (auto& item : *list) {
    Expression* expr = f({item});
    res->value.list->push_back(expr);
  }

  return res;
}

Expression* IsNumber(std::vector<Expression*> exprs) {
  return new Expression(
      new Symbol(exprs[0]->type == Expression::NUMBER ? "#t" : "#f"));
}

Expression* IsProcedure(std::vector<Expression*> exprs) {
  return new Expression(
      new Symbol(exprs[0]->type == Expression::PROC ? "#t" : "#f"));
}

Environment* StandardEnv() {
  Environment* env = new Environment();

  env->Insert("#t", new Expression(new Symbol("#t")));
  env->Insert("#f", new Expression(new Symbol("#f")));

  env->Insert("+", new Expression(Add));
  env->Insert("-", new Expression(Minus));
  env->Insert("*", new Expression(Product));
  env->Insert("/", new Expression(Divide));
  env->Insert(">", new Expression(Gt));
  env->Insert("<", new Expression(Lt));
  env->Insert(">=", new Expression(Ge));
  env->Insert("<=", new Expression(Le));
  env->Insert("=", new Expression(Eq));
  env->Insert("abs", new Expression(Abs));
  env->Insert("cons", new Expression(Cons));
  env->Insert("car", new Expression(Car));
  env->Insert("cdr", new Expression(Cdr));
  env->Insert("eq?", new Expression(SameAddress));
  env->Insert("equal?", new Expression(Eq));
  env->Insert("map", new Expression(Map));
  env->Insert("max", new Expression(Max));
  env->Insert("min", new Expression(Min));
  env->Insert("number?", new Expression(IsNumber));
  env->Insert("procedure?", new Expression(IsProcedure));

  return env;
}
}  // namespace scxx
