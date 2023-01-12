--------------------------------------------------------------
if        = (if predicate consequent alternative)
define    = (define symbol expression)
quotation = (quote expr)
lambda    = (lambda (symbol1 symbol2 ...) expr1 expr2 ...)
Special   = (if, define, quotation, lambda)
--------------------------------------------------------------
Primitive = (+ - * / ...)
Procedure = User-defined
Func      = (Procedure, Primitive)
Call      = (Func expr1 expr2 ...)
--------------------------------------------------------------
List      = (Call, Special)
--------------------------------------------------------------
Symbol    = string
Number    = double
Atom      = (Symbol, Number)
--------------------------------------------------------------
Expr      = (List, Atom)
--------------------------------------------------------------
Env       = map

