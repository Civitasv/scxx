#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Quotation {
  std::unique_ptr<Expression> quotes;

  Quotation();
  Quotation(const Expression& expr);
  Quotation(Expression&& expr);

  Quotation(const Quotation& quotation);
  Quotation(Quotation&& quotation);

  Quotation& operator=(const Quotation& quotation);
  Quotation& operator=(Quotation&& quotation);

  friend std::ostream& operator<<(std::ostream& os, const Quotation& quotation);
};
}  // namespace scxx
