#pragma once

#include <iostream>

#include "environment.h"
#include "type.h"

namespace scxx {
struct Procedure {
  std::unique_ptr<std::vector<Symbol>> params;
  std::unique_ptr<List> body;
  Environment* env;

  Procedure(const std::vector<Symbol>& params, const List& body,
            Environment* env);
  Procedure(std::vector<Symbol>&& params, List&& body, Environment* env);

  Procedure(const std::vector<Symbol>& params, const List& body);
  Procedure(std::vector<Symbol>&& params, List&& body);

  Procedure(const Procedure& procedure);
  Procedure(Procedure&& procedure);

  Procedure& operator=(const Procedure& procedure);
  Procedure& operator=(Procedure&& procedure);

  friend std::ostream& operator<<(std::ostream& os, const Procedure& call);
};
}  // namespace scxx
