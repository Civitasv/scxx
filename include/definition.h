#pragma once
#include <iostream>

#include "type.h"

namespace scxx {
struct Expression;

struct Definition {
  Symbol* variable;
  Expression* value;

  Definition(Symbol* variable, Expression* value);

  ~Definition();

  friend std::ostream& operator<<(std::ostream& os,
                                  const Definition& definition);
};
}  // namespace scxx
