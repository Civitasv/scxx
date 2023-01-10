#include "quotation.h"

#include <iostream>

#include "expression.h"

namespace scxx {
Quotation::Quotation() : quotes(nullptr) {}

Quotation::Quotation(const Expression& expr) : quotes(new Expression(expr)) {}

Quotation::Quotation(const Quotation& quotation) {
  quotes = new Expression(*quotation.quotes);
}

Quotation::~Quotation() {
  if (quotes) {
    delete quotes;
    quotes = nullptr;
  }
}

std::ostream& operator<<(std::ostream& os, const Quotation& quotation) {
  os << "QUOTES: " << *quotation.quotes;
  return os;
}
}  // namespace scxx
