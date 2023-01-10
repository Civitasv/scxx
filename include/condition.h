#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Condition {
  Expression* predicate;
  Expression* consequent;
  Expression* alternative;

  Condition();
  Condition(const Expression& predicate, const Expression& consequent,
     const Expression& alternative);
  Condition(const Condition& condition);

  ~Condition();

  friend std::ostream& operator<<(std::ostream& os, const Condition& If);
};
}  // namespace scxx
