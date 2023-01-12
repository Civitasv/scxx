Symbol    = string
Number    = double
Atom      = (Symbol, Number)

if        = (if predicate consequent alternative)
quotation = (quote expr)
lambda    = (lambda (symbol1 symbol2 ...) expr1 expr2 ...)
Special   = (if, define, quotation, lambda)

Primitive = (+ - * / ...)
Procedure = User-defined
Func      = (Procedure, Primitive)
Call      = (Func expr1 expr2 ...)

List      = (Call, Special)
Expr      = (List, Atom)

Env       = map
