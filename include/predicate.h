#pragma once

#include "expression.h"
#include "type.h"

namespace scxx {
inline bool IsFalse(Expression* expr) { return *expr->value.symbol == "#f"; }

inline bool IsTrue(Expression* expr) { return *expr->value.symbol != "#f"; }
}  // namespace scxx
