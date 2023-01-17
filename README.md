# Scheme interpreter In C++

> Make use of modern C++ and RAII.

## Usage

```sh
1 ]=> 1
;Value: 1
1 ]=> (+ 1 2)
;Value: 3
1 ]=> (define x 1)
;Value: x
1 ]=> (+ x 1)
;Value: 2
1 ]=> (define square (lambda (x) (* x x)))
;Value: square
1 ]=> (square 2)
;Value: 4
1 ]=> (if (> x 2) x 2)
;Value: 2
1 ]=> (cons 1 2)
;Value: '(1 2)
1 ]=> (car (cons 1 2))
;Value: 1
1 ]=> (cdr (cons 1 2))
;Value: 2
```

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
