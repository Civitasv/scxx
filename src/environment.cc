#include "environment.h"

#include "error.h"
#include "expression.h"

namespace scxx {
Environment::Environment() {}
Environment::Environment(std::vector<Symbol>& variables, List& values,
                         Environment* outer_env)
    : outer_env(outer_env) {
  if (variables.size() != values.size()) {
    panic("The size of variables must be equal to the size of values!");
  }
  for (int i = 0; i < variables.size(); i++) {
    Insert(variables[i], values[i]);
  }
}

Expression Environment::Find(const Symbol& variable) {
  if (env.find(variable) != env.end())
    return env[variable];
  else if (outer_env)
    return outer_env->Find(variable);
  else
    return {};
}

void Environment::Insert(const Symbol& variable, const Expression& expression) {
  env.insert_or_assign(variable, expression);
}

Environment::~Environment() {}

Expression Add(List& exprs) {
  double d = 0.0;
  for (auto& expr : exprs) {
    d += *expr.AsNumber();
  }
  return d;
}

Expression Minus(List& exprs) {
  double d = *exprs[0].AsNumber();
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    d -= *(expr.AsNumber());
  }
  return d;
}

Expression Product(List& exprs) {
  double d = 1.0;
  for (auto& expr : exprs) {
    d *= *(expr.AsNumber());
  }
  return d;
}

Expression Divide(List& exprs) {
  double d = *exprs[0].AsNumber();
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    d /= *(expr.AsNumber());
  }
  return d;
}

Expression Gt(List& exprs) {
  double d = *exprs[0].AsNumber();
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d <= *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Lt(List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d >= *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Ge(List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d < *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Le(List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d > *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Eq(List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d != *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Abs(List& exprs) {
  double d = std::abs(*(exprs[0].AsNumber()));
  return d;
}

Expression Cons(List& exprs) {
  List list;
  list.push_back(exprs[0]);
  list.push_back(exprs[1]);
  return Quotation(list);
}

Expression Car(List& exprs) {
  return (*exprs[0].AsQuotation()->quotes->AsList())[0];
}

Expression Cdr(List& exprs) {
  return (*exprs[0].AsQuotation()->quotes->AsList())[1];
}

Expression Max(List& exprs) {
  double max = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (max < *(expr.AsNumber())) max = *(expr.AsNumber());
  }
  return max;
}

Expression Min(List& exprs) {
  double min = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (min > *(expr.AsNumber())) min = *(expr.AsNumber());
  }
  return min;
}

Expression Empty(List& exprs) {
  List list = *exprs[0].AsList();
  return list.size() == 0 ? Symbol("#t") : Symbol("#f");
}

Environment* Environment::StandardEnv() {
  Environment* env = new Environment();

  env->Insert("#t", Expression("#t"));
  env->Insert("#f", Expression("#f"));

  env->Insert("+", Primitive("+", Add));
  env->Insert("-", Primitive("-", Minus));
  env->Insert("*", Primitive("*", Product));
  env->Insert("/", Primitive("/", Divide));
  env->Insert(">", Primitive(">", Gt));
  env->Insert("<", Primitive("<", Lt));
  env->Insert(">=", Primitive(">=", Ge));
  env->Insert("<=", Primitive("<=", Le));
  env->Insert("=", Primitive("=", Eq));
  env->Insert("abs", Primitive("abs", Abs));
  env->Insert("cons", Primitive("cons", Cons));
  env->Insert("car", Primitive("car", Car));
  env->Insert("cdr", Primitive("cdr", Cdr));
  env->Insert("equal?", Primitive("equal?", Eq));
  env->Insert("max", Primitive("max", Max));
  env->Insert("min", Primitive("min", Min));
  env->Insert("empty?", Primitive("empty?", Empty));

  return env;
}
}  // namespace scxx
