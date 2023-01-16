#include "call.h"

#include <cstddef>

#include "expression.h"

namespace scxx {
Call::Call()
    : proc(std::make_unique<Expression>()), args(std::make_unique<List>()) {}

Call::Call(const Expression& proc, const List& args)
    : proc(std::make_unique<Expression>(proc)),
      args(std::make_unique<List>(args)) {}

Call::Call(Expression&& proc, List&& args)
    : proc(std::make_unique<Expression>(std::move(proc))),
      args(std::make_unique<List>(std::move(args))) {}

Call::Call(const Call& call)
    : proc(std::make_unique<Expression>(*call.proc)),
      args(std::make_unique<List>(*call.args)) {}

Call::Call(Call&& call)
    : proc(std::move(call.proc)), args(std::move(call.args)) {}

Call& Call::operator=(const Call& call) {
  proc = std::make_unique<Expression>(*call.proc);
  args = std::make_unique<List>(*call.args);
  return *this;
}

Call& Call::operator=(Call&& call) {
  proc = std::move(call.proc);
  args = std::move(call.args);
  return *this;
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
}  // namespace scxx
