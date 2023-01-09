#pragma once
#include <iostream>

#include "type.h"

namespace scxx {
struct Procedure {
  Symbol* proc_name;
  std::vector<Expression*> args;

  Procedure(Symbol* proc_name, std::vector<Expression*> args);

  ~Procedure();

  friend std::ostream& operator<<(std::ostream& os,
                                  const Procedure& definition);
};
}  // namespace scxx
