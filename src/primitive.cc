#include "primitive.h"

#include "expression.h"
#include "type.h"

namespace scxx {

Primitive::Primitive() : proc_name(nullptr), proc(nullptr) {}

Primitive::Primitive(const Symbol& proc_name, const Proc& proc)
    : proc_name(std::make_unique<Symbol>(proc_name)), proc(proc) {}

Primitive::Primitive(Symbol&& proc_name, Proc&& proc)
    : proc_name(std::make_unique<Symbol>(std::move(proc_name))), proc(proc) {}

Primitive::Primitive(const Primitive& primitive)
    : proc_name(std::make_unique<Symbol>(*primitive.proc_name)),
      proc(primitive.proc) {}

Primitive::Primitive(Primitive&& primitive)
    : proc_name(std::move(primitive.proc_name)), proc(primitive.proc) {}

Primitive& Primitive::operator=(const Primitive& primitive) {
  proc_name = std::make_unique<Symbol>(*primitive.proc_name);
  proc = primitive.proc;
  return *this;
}

Primitive& Primitive::operator=(Primitive&& primitive) {
  proc_name = std::move(primitive.proc_name);
  proc = primitive.proc;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Primitive& primitive) {
  os << "[Primitive: " << *primitive.proc_name << " ";
  return os;
}

Expression Add(const List& exprs) {
  double d = 0.0;
  for (auto& expr : exprs) {
    d += *expr.AsNumber();
  }
  return d;
}

Expression Minus(const List& exprs) {
  double d = *exprs[0].AsNumber();
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    d -= *(expr.AsNumber());
  }
  return d;
}

Expression Product(const List& exprs) {
  double d = 1.0;
  for (auto& expr : exprs) {
    d *= *(expr.AsNumber());
  }
  return d;
}

Expression Divide(const List& exprs) {
  double d = *exprs[0].AsNumber();
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    d /= *(expr.AsNumber());
  }
  return d;
}

Expression Gt(const List& exprs) {
  double d = *exprs[0].AsNumber();
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d <= *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Lt(const List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d >= *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Ge(const List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d < *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Le(const List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d > *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Eq(const List& exprs) {
  double d = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (d != *(expr.AsNumber())) return Symbol("#f");
  }
  return Symbol("#t");
}

Expression Abs(const List& exprs) {
  double d = std::abs(*(exprs[0].AsNumber()));
  return d;
}

Expression Cons(const List& exprs) {
  List list;
  list.push_back(exprs[0]);
  list.push_back(exprs[1]);
  return Quotation(list);
}

Expression Car(const List& exprs) {
  return (*exprs[0].AsQuotation()->quotes->AsList())[0];
}

Expression Cdr(const List& exprs) {
  return (*exprs[0].AsQuotation()->quotes->AsList())[1];
}

Expression Max(const List& exprs) {
  double max = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (max < *(expr.AsNumber())) max = *(expr.AsNumber());
  }
  return max;
}

Expression Min(const List& exprs) {
  double min = *(exprs[0].AsNumber());
  for (int i = 1; i < exprs.size(); i++) {
    Expression expr = exprs[i];
    if (min > *(expr.AsNumber())) min = *(expr.AsNumber());
  }
  return min;
}

Expression Empty(const List& exprs) {
  List list = *exprs[0].AsList();
  return list.size() == 0 ? Symbol("#t") : Symbol("#f");
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
  env->Insert("empty?", Primitive("empty?", Empty));

  return env;
}
}  // namespace scxx
