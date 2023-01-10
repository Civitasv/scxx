#include "procedure.h"

#include "expression.h"

namespace scxx {
Procedure::Procedure(const std::vector<Symbol>& params, const List& body,
                     Environment* env)
    : params(new std::vector<Symbol>(params)), body(new List(body)), env(env) {}

Procedure::Procedure(const std::vector<Symbol>& params, const List& body)
    : params(new std::vector<Symbol>(params)),
      body(new List(body)),
      env(nullptr) {}

Procedure::Procedure(const Procedure& procedure) {
  params = new std::vector<Symbol>(*procedure.params);
  body = new List(*procedure.body);
}

std::ostream& operator<<(std::ostream& os, const Procedure& procedure) {
  os << "[Procedure: ";
  os << "Params: ";
  for (auto& item : *procedure.params) std::cout << item << " ";
  os << "Body: " << *procedure.body << " ";
  os << "]";
  return os;
}

Procedure::~Procedure() {
  if (params) {
    delete params;
    params = nullptr;
  }
  if (body) {
    delete body;
    body = nullptr;
  }
}
}  // namespace scxx
