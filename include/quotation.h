#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Quotation {
  Expression* quotes;

  Quotation();
  Quotation(const Expression& expr);

  Quotation(const Quotation& quotation);

  ~Quotation();

  friend std::ostream& operator<<(std::ostream& os, const Quotation& quotation);
};
}  // namespace scxx
