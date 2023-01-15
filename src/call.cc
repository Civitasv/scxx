#include "call.h"

#include <cstddef>

#include "expression.h"

namespace scxx {
Call::Call() : proc(nullptr), args(nullptr) {}

Call::Call(const Expression& proc, const List& args)
    : proc(new Expression(proc)), args(new List(args)) {}

Call::Call(const Call& call) {
  proc = new Expression(*call.proc);
  args = new List(*call.args);
}

std::ostream& operator<<(std::ostream& os, const Call& call) {
  os << "[Call: " << *call.proc << " ";
  os << "Args: ";
  for (auto& item : *call.args) {
    os << item << " ";
  }
  os << "]";
  return os;
}

Call::~Call() {
  if (proc) {
    delete proc;
    proc = nullptr;
  }
  if (args) {
    delete args;
    args = nullptr;
  }
}
}  // namespace scxx
