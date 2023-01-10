#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Definition {
  Symbol* variable;
  Expression* value;

  Definition(const Symbol& variable, const Expression& value);
  Definition(const Definition& definition);

  ~Definition();

  friend std::ostream& operator<<(std::ostream& os,
                                  const Definition& definition);
};
}  // namespace scxx
