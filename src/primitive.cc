#include "primitive.h"

#include "expression.h"
#include "type.h"

namespace scxx {

Primitive::Primitive() : proc_name(nullptr), proc(nullptr) {}

Primitive::Primitive(const Symbol& proc_name, const Proc& proc)
    : proc_name(std::make_unique<Symbol>(proc_name)), proc(proc) {}

Primitive::Primitive(Symbol&& proc_name, Proc&& proc)
    : proc_name(std::make_unique<Symbol>(std::move(proc_name))), proc(proc) {}

Primitive::Primitive(const Primitive& primitive)
    : proc_name(std::make_unique<Symbol>(*primitive.proc_name)),
      proc(primitive.proc) {}

Primitive::Primitive(Primitive&& primitive)
    : proc_name(std::move(primitive.proc_name)), proc(primitive.proc) {}

Primitive& Primitive::operator=(const Primitive& primitive) {
  proc_name = std::make_unique<Symbol>(*primitive.proc_name);
  proc = primitive.proc;
  return *this;
}

Primitive& Primitive::operator=(Primitive&& primitive) {
  proc_name = std::move(primitive.proc_name);
  proc = primitive.proc;
  return *this;
}

std::ostream& operator<<(std::ostream& os, Primitive& primitive) {
  os << "[Primitive: " << *primitive.proc_name << "]";
  return os;
}
}  // namespace scxx
