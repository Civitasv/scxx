# Scheme interpreter In C++

> Make use of modern C++ and RAII.

## Spec

```txt
--------------------------------------------------------------
if        = (if predicate consequent alternative)
define    = (define symbol expression)
quotation = (quote expr)
lambda    = (lambda (symbol1 symbol2 ...) expr1 expr2 ...)
Special   = (if, define, quotation, lambda)
--------------------------------------------------------------
Primitive = (+ - * / ...)
Procedure = User-defined
Function  = (Procedure, Primitive)
Call      = (Function expr1 expr2 ...)
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
```

## Steps

Program => Scanner(Tokens) => Parser(AST) => Eval(Result)

### Scanner

Also called lexical analysis, it scans all the source code, and get tokens.

Example:

    "var average = (min + max) / 2;" ->:
    "var" "average" "=" "(" "min" "+" "max" ")" "/" "2" ";"

### Parser

Get Abstract syntax tree.
And get syntax errors.

###  Evaluation

Retrieve calculation result from AST.

## Reference

1.  [cxxopts](https://github.com/jarro2783/cxxopts): A lightweight C++ command line option parser
2.  [craftinginterpreters](https://craftinginterpreters.com/a-map-of-the-territory.html): Lox
