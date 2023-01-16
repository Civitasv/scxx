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

  friend std::ostream& operator<<(std::ostream& os, const Primitive& primitive);
};

Expression Add(const List& exprs);
Expression Minus(const List& exprs);
Expression Product(const List& exprs);
Expression Divide(const List& exprs);

Expression Gt(const List& exprs);
Expression Lt(const List& exprs);
Expression Ge(const List& exprs);
Expression Le(const List& exprs);
Expression Eq(const List& exprs);
Expression Abs(const List& exprs);
Expression Cons(const List& exprs);
Expression Car(const List& exprs);
Expression Cdr(const List& exprs);
Expression Max(const List& exprs);
Expression Min(const List& exprs);
Expression Empty(const List& exprs);

Environment* StandardEnv();
}  // namespace scxx
