#pragma once

#include <iostream>

#include "environment.h"
#include "type.h"

namespace scxx {
struct Procedure {
  std::vector<Symbol>* params;
  List* body;
  Environment* env;

  Procedure(const std::vector<Symbol>& params, const List& body,
            Environment* env);
  Procedure(const std::vector<Symbol>& params, const List& body);
  Procedure(const Procedure& procedure);

  ~Procedure();

  friend std::ostream& operator<<(std::ostream& os, const Procedure& call);
};
}  // namespace scxx
