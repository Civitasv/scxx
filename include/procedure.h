#pragma once
#include <iostream>

#include "type.h"

namespace scxx {
struct Procedure {
  Expression* proc;
  std::vector<Expression*> args;

  Procedure(Expression* proc, std::vector<Expression*> args);

  ~Procedure();

  friend std::ostream& operator<<(std::ostream& os,
                                  const Procedure& definition);
};
}  // namespace scxx
