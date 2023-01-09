﻿#pragma once

#include <string>
#include <vector>

namespace scxx {
struct Expression;
using Symbol = std::string;
using Number = double;
typedef std::vector<Expression*> List;
typedef Expression* (*Proc)(std::vector<Expression*>);
}  // namespace scxx
