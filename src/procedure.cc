#include "procedure.h"

#include "expression.h"

namespace scxx {
Procedure::Procedure(const std::vector<Symbol>& params, const List& body,
                     Environment* env)
    : params(std::make_unique<std::vector<Symbol>>(params)),
      body(std::make_unique<List>(body)),
      env(env) {}

Procedure::Procedure(std::vector<Symbol>&& params, List&& body,
                     Environment* env)
    : params(std::make_unique<std::vector<Symbol>>(std::move(params))),
      body(std::make_unique<List>(std::move(body))),
      env(env) {}

Procedure::Procedure(const std::vector<Symbol>& params, const List& body)
    : params(std::make_unique<std::vector<Symbol>>(params)),
      body(std::make_unique<List>(body)),
      env(nullptr) {}

Procedure::Procedure(std::vector<Symbol>&& params, List&& body)
    : params(std::make_unique<std::vector<Symbol>>(std::move(params))),
      body(std::make_unique<List>(std::move(body))),
      env(nullptr) {}

Procedure::Procedure(const Procedure& procedure)
    : params(std::make_unique<std::vector<Symbol>>(*procedure.params)),
      body(std::make_unique<List>(*procedure.body)),
      env(procedure.env) {}

Procedure::Procedure(Procedure&& procedure)
    : params(std::move(procedure.params)),
      body(std::move(procedure.body)),
      env(procedure.env) {}

Procedure& Procedure::operator=(const Procedure& procedure) {
  params = std::make_unique<std::vector<Symbol>>(*procedure.params);
  body = std::make_unique<List>(*procedure.body);
  env = procedure.env;
  return *this;
}

Procedure& Procedure::operator=(Procedure&& procedure) {
  params = std::move(procedure.params);
  body = std::move(procedure.body);
  env = procedure.env;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Procedure& procedure) {
  os << "[Procedure: ";
  os << "Params: ";
  for (auto& item : *procedure.params) std::cout << item << " ";
  os << "Body: " << *procedure.body << " ";
  os << "]";
  return os;
}
}  // namespace scxx
