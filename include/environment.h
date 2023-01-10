#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "type.h"

namespace scxx {
class Environment {
 public:
  Environment();
  Environment(std::vector<Symbol> variables, List values,
              Environment* outer_env);

  Expression Find(Symbol variable);

  void Insert(const Symbol& variable, const Expression& expression);

  ~Environment();

 private:
  std::unordered_map<Symbol, Expression> env;
  Environment* outer_env;
};
}  // namespace scxx
