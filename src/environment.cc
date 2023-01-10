#include "environment.h"

#include "error.h"
#include "expression.h"

namespace scxx {
Environment::Environment() {}
Environment::Environment(std::vector<Symbol> variables,
                         std::vector<Expression> values, Environment* outer_env)
    : outer_env(outer_env) {
  if (variables.size() != values.size()) {
    Error("The size of variables must be equal to the size of values!");
  }
  for (int i = 0; i < variables.size(); i++) {
    env[variables[i]] = values[i];
  }
}

Expression Environment::Find(Symbol variable) {
  if (env.find(variable) != env.end())
    return env[variable];
  else if (outer_env)
    return outer_env->Find(variable);
  else
    return nullptr;
}

void Environment::Insert(const Symbol& variable, const Expression& expression) {
  env.insert_or_assign(variable, expression);
}

Environment::~Environment() {}
}  // namespace scxx
