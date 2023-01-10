#include "primitive.h"

#include "type.h"

namespace scxx {
Expression Add(const List& exprs) {
  double d = 0.0;
  for (auto& expr : exprs) {
    d += *(expr.value.number);
  }
  return d;
}

Expression Minus(const List& exprs) {
  double d = *exprs[0].value.number;
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    d -= *(expr.value.number);
  }
  return d;
}

Expression Product(const List& exprs) {
  double d = 1.0;
  for (auto& expr : exprs) {
    d *= *(expr.value.number);
  }
  return d;
}

Expression Divide(const List& exprs) {
  double d = *exprs[0].value.number;
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    d /= *(expr.value.number);
  }
  return d;
}

Expression Gt(const List& exprs) {
  double d = *exprs[0].value.number;
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d <= *(expr.value.number)) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Lt(const List& exprs) {
  double d = *(exprs[0].value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d >= *(expr.value.number)) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Ge(const List& exprs) {
  double d = *(exprs[0].value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d < *(expr.value.number)) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Le(const List& exprs) {
  double d = *(exprs[0].value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d > *(expr.value.number)) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Eq(const List& exprs) {
  double d = *(exprs[0].value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d != *(expr.value.number)) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Abs(const List& exprs) {
  double d = std::abs(*(exprs[0].value.number));
  return d;
}

Expression Cons(const List& exprs) { return List({exprs[0], exprs[1]}); }

Expression Car(const List& exprs) { return (*exprs[0].value.list)[0]; }

Expression Cdr(const List& exprs) { return (*exprs[0].value.list)[1]; }

Expression SameAddress(const List& exprs) { return Symbol("#t"); }

Expression Max(const List& exprs) {
  double max = *(exprs[0].value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (max < *(expr.value.number)) max = *(expr.value.number);
  }
  return max;
}

Expression Min(const List& exprs) {
  double min = *(exprs[0].value.number);
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (min > *(expr.value.number)) min = *(expr.value.number);
  }
  return min;
}

Expression Map(const List& exprs) {
  Proc f = exprs[0].value.proc;
  const List& list = (*exprs[1].value.quotation->quotes->value.list);

  Expression res = Expression::QUOTATION;

  for (auto& item : list) {
    Expression expr = f(List{item});
    res.value.quotation->quotes->value.list->push_back(expr);
  }

  return res;
}

Expression IsNumber(const List& exprs) {
  return Symbol(exprs[0].type == Expression::NUMBER ? "#t" : "#f");
}

Expression IsProcedure(const List& exprs) {
  return Symbol(exprs[0].type == Expression::PROC ? "#t" : "#f");
}

Environment* StandardEnv() {
  Environment* env = new Environment();

  env->Insert("#t", Symbol("#t"));
  env->Insert("#f", Symbol("#f"));

  env->Insert("+", Add);
  env->Insert("-", Minus);
  env->Insert("*", Product);
  env->Insert("/", Divide);
  env->Insert(">", Gt);
  env->Insert("<", Lt);
  env->Insert(">=", Ge);
  env->Insert("<=", Le);
  env->Insert("=", Eq);
  env->Insert("abs", Abs);
  env->Insert("cons", Cons);
  env->Insert("car", Car);
  env->Insert("cdr", Cdr);
  env->Insert("eq?", SameAddress);
  env->Insert("equal?", Eq);
  env->Insert("map", Map);
  env->Insert("max", Max);
  env->Insert("min", Min);
  env->Insert("number?", IsNumber);
  env->Insert("procedure?", IsProcedure);

  return env;
}
}  // namespace scxx
