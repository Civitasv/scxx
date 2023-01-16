#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Definition {
  std::unique_ptr<Symbol> variable;
  std::unique_ptr<Expression> value;

  Definition(const Symbol& variable, const Expression& value);
  Definition(Symbol&& variable, Expression&& value);

  Definition(const Definition& definition);
  Definition(Definition&& definition);

  Definition& operator=(const Definition& definition);
  Definition& operator=(Definition&& definition);

  friend std::ostream& operator<<(std::ostream& os,
                                  const Definition& definition);
};
}  // namespace scxx
