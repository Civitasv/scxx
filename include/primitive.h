#pragma once

#include <vector>

#include "environment.h"

namespace scxx {
struct Primitive {
  std::unique_ptr<Symbol> proc_name;
  Proc proc;

  Primitive();
  Primitive(const Symbol& proc_name, const Proc& proc);
  Primitive(Symbol&& proc_name, Proc&& proc);

  Primitive(const Primitive& primitive);
  Primitive(Primitive&& primitive);

  Primitive& operator=(const Primitive& primitive);
  Primitive& operator=(Primitive&& primitive);

  friend std::ostream& operator<<(std::ostream& os, Primitive& primitive);
};

Expression Add(List& exprs);
Expression Minus(List& exprs);
Expression Product(List& exprs);
Expression Divide(List& exprs);

Expression Gt(List& exprs);
Expression Lt(List& exprs);
Expression Ge(List& exprs);
Expression Le(List& exprs);
Expression Eq(List& exprs);
Expression Abs(List& exprs);
Expression Cons(List& exprs);
Expression Car(List& exprs);
Expression Cdr(List& exprs);
Expression Max(List& exprs);
Expression Min(List& exprs);
Expression Empty(List& exprs);

Environment* StandardEnv();
}  // namespace scxx
