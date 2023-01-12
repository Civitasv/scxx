# Scheme interpreter In C++ from Scratch

## 执行流程

Program => Scanner => Tokens => Parser => AST => Eval => Result

### Scanner

又称词法分析(lexical analysis)，用于扫描字符串，获得所有 tokens.

Example:

    "var average = (min + max) / 2;" ->:
    "var" "average" "=" "(" "min" "+" "max" ")" "/" "2" ";"

Implementation:

### Parser

Get Abstract syntax tree.
And get syntax errors.

### Static analysis

类型。

### Intermediate representations

Java 有 JVM，正是一种 intermediate representations。
Not include this!

### Optimization

Not include this!

### Code generation

Virtual machine byte code? Or native code.

或者使用 _Transpilers_ ，即将 原始代码 编译为 目标语言代码，然后使用目标语言的编译器执行该目标代码。

Not include this!

### Runtime

Garbage collector, type.

编译语言中，runtime 会直接在 executable file 中（Go 语言是这样的），但如果该语言在解释器或 Virtual Machine 中执行，runtime 会在解释器或 VM 中（Java、Python、JavaScript 是这样的）。

Not include this!

### 总结

1.  Scanner, lexical analysis
2.  Parser, get abstract syntax tree
3.  Evaluation, in C++

## Scheme 语法

### Number/Symbol

Atomic expressions.

    1 ;; 1, 1 is a number

    ;; (define a 1)
    a ;; 1, a is a symbol

其他的都是 List expressions.

How beautiful!

### 算术操作

    (/ 10 5) ;; 2
    (+ 1 2) ;; 3

如表达式 `(/ 10 5)` ， `/` 是算子， `10 5` 是操作数。

## 变量

    (define q (+ 1 2)) ;; q will be 3

### 函数

    (define (square x) (* x x))

### cond/if

用于条件判断。

    (cond (<p1> <e1>)
          (<p2> <e2>)
          (<p3> <e3>)
          ...
          (<p4> <e4>)
          (else <other>))

    (if <p> <result> <alternative>)

### 逻辑判断

    (and <p1> <p2> ... <pn>)
    (or <p1> <p2> ... <pn>)
    (not <p1>)

### List

    (define a (cons 1 (cons 2 (cons 3 '()))))

    (car a) ;; 1
    (cadr a) ;; 2
    (length a) ;; 3

    (define (map proc items)
      (if (null? items)
          '()
          (cons (proc (car items)) (map proc (cdr items)))))

## Some Good Knowledge

### 编译器 vs 解释器

a. 编译器（compiler）将 **源代码** 从一种较高级的形式 转变为 较低级的形式，编译后 **不直接执行**
b. 解释器（interpreter）直接执行 **源代码**

但事实上，现实世界中的编译器和解释器不是非此即彼，而是常常你中有我。

### Lisp

Lisp 有诸多的实现，

### 动态类型 vs 静态类型

[Comparison](https://www.baeldung.com/cs/statically-vs-dynamically-typed-languages)

#### 动态类型语言，但是存在编译实现

1.  LuaJIT, just-in-time compiler
2.  Chez scheme, scheme compiler

Why?

Better performance!

如果对动态类型语言使用编译器编译，那么类型也得在编译阶段确定。

#### 静态类型语言，但是存在解释实现

很稀有。

1.  Objective Caml.

Why?

Easy to debug.

如果对静态类型语言使用解释器解释，那么类型检查应该是在运行阶段。

#### 总结

动态类型，或是静态类型，与编译还是解释没有直接的关联。
但是动态类型往往是解释型语言，静态类型往往是编译型语言。这可能是因为 动态类型 相比于 静态类型，没那么“严肃”，也不是为高性能而设计的。

感觉如果对静态类型语言使用解释器，那么这个静态类型语言此时应该叫“动态类型语言了”，毕竟编程语言只是字符串的集合而已，真正重要的是如何去解析它。

## Reference

1.  [cxxopts](https://github.com/jarro2783/cxxopts): A lightweight C++ command line option parser
2.  [craftinginterpreters](https://craftinginterpreters.com/a-map-of-the-territory.html): Lox
3.  [语义化标签](https://semver.org/lang/zh-CN/): 如何发布版本
