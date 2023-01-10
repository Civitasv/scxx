#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Call {
  Symbol* proc_name;
  List* args;

  Call();
  Call(const Symbol& proc_name, const List& args);
  Call(const Call& call);

  ~Call();

  friend std::ostream& operator<<(std::ostream& os, const Call& call);
};
}  // namespace scxx
