#pragma once

#include <memory>
#include <string>
#include <vector>

namespace scxx {
struct Expression;
using Symbol = std::string;
using Number = double;
typedef std::vector<Expression> List;
typedef Expression (*Proc)(const List&);
}  // namespace scxx
