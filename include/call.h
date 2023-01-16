#pragma once

#include <iostream>

#include "type.h"

namespace scxx {
struct Call {
  std::unique_ptr<Expression> proc;
  std::unique_ptr<List> args;

  Call();
  Call(const Expression& proc, const List& args);
  Call(Expression&& proc, List&& args);
  // copy constructor
  Call(const Call& call);
  // move constructor
  Call(Call&& call);

  // copy assignment
  Call& operator=(const Call& call);
  // move assignment
  Call& operator=(Call&& call);

  friend std::ostream& operator<<(std::ostream& os, const Call& call);
};
}  // namespace scxx
