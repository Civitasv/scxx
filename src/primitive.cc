#include "primitive.h"

#include "expression.h"
#include "type.h"

namespace scxx {

Primitive::Primitive() : proc_name(nullptr), proc(nullptr) {}

Primitive::Primitive(const Symbol& proc_name, const Proc& proc)
    : proc_name(new Symbol(proc_name)), proc(proc) {}

Primitive::Primitive(const Primitive& primitive) {
  proc_name = new Symbol(*primitive.proc_name);
  proc = primitive.proc;
}

std::ostream& operator<<(std::ostream& os, const Primitive& primitive) {
  os << "[Primitive: " << *primitive.proc_name << " ";
  return os;
}

Primitive::~Primitive() {
  if (proc_name) {
    delete proc_name;
    proc_name = nullptr;
  }
}

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

Environment* StandardEnv() {
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

  return env;
}
}  // namespace scxx
