#pragma once

#include <vector>

#include "type.h"

namespace scxx {
struct Primitive {
  std::unique_ptr<Symbol> proc_name;
  Proc proc;

  Primitive();
  Primitive(const Symbol& proc_name, const Proc& proc);
  Primitive(Symbol&& proc_name, Proc&& proc);

  Primitive(const Primitive& primitive);
  Primitive(Primitive&& primitive);

  Primitive& operator=(const Primitive& primitive);
  Primitive& operator=(Primitive&& primitive);

  friend std::ostream& operator<<(std::ostream& os, Primitive& primitive);
};
}  // namespace scxx
