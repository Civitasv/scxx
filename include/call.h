#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Call {
  Expression* proc;
  List* args;

  Call();
  Call(const Expression& proc, const List& args);
  Call(const Call& call);

  ~Call();

  friend std::ostream& operator<<(std::ostream& os, const Call& call);
};
}  // namespace scxx
