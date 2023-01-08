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
  Environment(std::vector<Symbol*> variables, std::vector<Expression*> values,
              Environment* outer_env);

  Expression* Find(Symbol* variable);

  void Insert(Symbol* variable, Expression* expression);

 private:
  std::unordered_map<Symbol*, Expression*> env;
  Environment* outer_env;
};
}  // namespace scxx
