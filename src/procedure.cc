#include "procedure.h"

#include "expression.h"

namespace scxx {
Procedure::Procedure(Expression* proc, std::vector<Expression*> args)
    : proc(proc), args(args) {}

std::ostream& operator<<(std::ostream& os, const Procedure& procedure) {
  os << "Proc: " << *procedure.proc << " ";
  os << "Args: "
     << " ";
  for (auto& item : procedure.args) {
    os << *item;
  }
  return os;
}

Procedure::~Procedure() {
  if (proc) delete proc;
  for (auto& item : args) delete item;
}
}  // namespace scxx
