#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

namespace scxx {
inline void Error(const std::string& message) {
  std::cerr << message << '\n';
  throw std::runtime_error(message);
}
}  // namespace scxx
