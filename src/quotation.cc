#include "quotation.h"

#include <iostream>

#include "expression.h"

namespace scxx {
Quotation::Quotation() : quotes(nullptr) {}

Quotation::Quotation(const Expression& expr)
    : quotes(std::make_unique<Expression>(expr)) {}

Quotation::Quotation(Expression&& expr)
    : quotes(std::make_unique<Expression>(std::move(expr))) {}

Quotation::Quotation(const Quotation& quotation)
    : quotes(std::make_unique<Expression>(*quotation.quotes)) {}

Quotation::Quotation(Quotation&& quotation)
    : quotes(std::move(quotation.quotes)) {}

Quotation& Quotation::operator=(const Quotation& quotation) {
  quotes = std::make_unique<Expression>(*quotation.quotes);
  return *this;
}

Quotation& Quotation::operator=(Quotation&& quotation) {
  quotes = std::move(quotation.quotes);
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Quotation& quotation) {
  os << "'" << *quotation.quotes;
  return os;
}
}  // namespace scxx
