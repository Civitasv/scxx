#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Condition {
  std::unique_ptr<Expression> predicate;
  std::unique_ptr<Expression> consequent;
  std::unique_ptr<Expression> alternative;

  Condition();
  Condition(const Expression& predicate, const Expression& consequent,
            const Expression& alternative);
  Condition(Expression&& predicate, Expression&& consequent,
            Expression&& alternative);
  Condition(const Condition& condition);
  Condition(Condition&& condition);

  Condition& operator=(const Condition& condition);
  Condition& operator=(Condition&& condition);

  friend std::ostream& operator<<(std::ostream& os, const Condition& If);
};
}  // namespace scxx
