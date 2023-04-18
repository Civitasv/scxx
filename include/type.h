#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace scxx {
class Environment;
struct Expression;
using Symbol = std::string;
using Number = double;
using List = std::vector<Expression>;
using Proc = std::function<Expression(List&)>;
}  // namespace scxx
