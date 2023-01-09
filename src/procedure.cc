#include "procedure.h"

#include "expression.h"

namespace scxx {
Procedure::Procedure(Symbol* proc_name, std::vector<Expression*> args)
    : proc_name(proc_name), args(args) {}

std::ostream& operator<<(std::ostream& os, const Procedure& procedure) {
  os << "Proc: " << *procedure.proc_name << " ";
  os << "Args: "
     << " ";
  for (auto& item : procedure.args) {
    os << *item;
  }
  return os;
}

Procedure::~Procedure() {
  delete proc_name;
  for (auto& item : args) delete item;
}
}  // namespace scxx
