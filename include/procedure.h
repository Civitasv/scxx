#pragma once
#include <iostream>

#include "type.h"

namespace scxx {
struct Procedure {
  Symbol* proc_name;
  List* args;

  Procedure(const Symbol& proc_name, const List& args);
  Procedure(const Procedure& procedure);

  ~Procedure();

  friend std::ostream& operator<<(std::ostream& os,
                                  const Procedure& definition);
};
}  // namespace scxx
