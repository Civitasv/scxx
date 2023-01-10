#include "procedure.h"

#include "expression.h"

namespace scxx {
Procedure::Procedure(const Symbol& proc_name, const List& args)
    : proc_name(new Symbol(proc_name)), args(new List(args)) {}

Procedure::Procedure(const Procedure& procedure) {
  proc_name = new Symbol(*procedure.proc_name);
  args = new List(*procedure.args);
}

std::ostream& operator<<(std::ostream& os, const Procedure& procedure) {
  os << "[Proc: " << *procedure.proc_name << " ";
  os << "Args: ";
  for (auto& item : *procedure.args) {
    os << item << " ";
  }
  os << "]";
  return os;
}

Procedure::~Procedure() {
  if (proc_name) {
    delete proc_name;
    proc_name = nullptr;
  }
  if (args) {
    delete args;
    args = nullptr;
  }
}
}  // namespace scxx
