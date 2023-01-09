1. EASY
1.1 ATOMIC EXPRESSIONS:
  - symbol => string
  - number => double
1.2 SPECIAL FORMS:
  - if
  - define
1.3 PROC
  - proc

Symbol    = string
Number    = double
Atom      = (Symbol, Number)
Special   = (if, define)
Primitive = (+ - * /)
Proc      = (Primitive, User-defined)
Func      = (Special, Proc)
List      = (Func expr1 expr2 ...)
Expr      = (List, Atom)
Env       = map
