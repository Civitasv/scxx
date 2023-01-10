Symbol    = string
Number    = double
Atom      = (Symbol, Number)

Special   = (if, define, quotation, lambda)

Primitive = (+ - * / ...)
Procedure = User-defined
Func      = (Procedure, Primitive)
Call      = (Func expr1 expr2 ...)

List      = (Call, Special)
Expr      = (List, Atom)

Env       = map
