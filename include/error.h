#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

namespace scxx {
inline void panic(const std::string& message) {
  std::cerr << "panic! " << message << '\n';
  exit(1);
}
}  // namespace scxx
