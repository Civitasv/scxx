#pragma once

#include "expression.h"
#include "type.h"

namespace scxx {
inline bool IsFalse(Expression* expr) { return *expr->AsSymbol() == "#f"; }

inline bool IsTrue(Expression* expr) { return *expr->AsSymbol() != "#f"; }
}  // namespace scxx
