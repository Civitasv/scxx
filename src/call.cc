#include "call.h"

#include <cstddef>

#include "expression.h"

namespace scxx {
Call::Call() : proc_name(nullptr), args(nullptr) {}

Call::Call(const Symbol& proc_name, const List& args)
    : proc_name(new Symbol(proc_name)), args(new List(args)) {}

Call::Call(const Call& call) {
  proc_name = new Symbol(*call.proc_name);
  args = new List(*call.args);
}

std::ostream& operator<<(std::ostream& os, const Call& call) {
  os << "[Call: " << *call.proc_name << " ";
  os << "Args: ";
  for (auto& item : *call.args) {
    os << item << " ";
  }
  os << "]";
  return os;
}

Call::~Call() {
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
