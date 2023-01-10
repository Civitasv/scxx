#pragma once

#include <vector>

#include "definition.h"
#include "error.h"
#include "expression.h"
#include "lexer.h"
#include "type.h"

namespace scxx {
class Parser {
 private:
  int pos;
  bool quotation;

 public:
  Expression Parse(std::vector<Token> tokens) {
    pos = 0;
    quotation = false;
    // 1. first, 将 List 和 Atom, Func 分开
    Expression expr = First(tokens);
    // 2. second, 处理 List, 分开为 define, quotation, procedure
    Expression result = Second(expr);
    return result;
  }

 private:
  Expression First(std::vector<Token> tokens) {
    if (tokens.size() == pos) {
      Error("Unexpected EOF");
    }
    Token token = tokens[pos++];
    if (token.type == Token::RIGHT_PAREN) {
      // if it is ')'
      Error("Syntax error: )");
    } else if (token.type == Token::LEFT_PAREN) {  // Expression
      // if it is '(', go on until we met ')'
      List list;
      while (tokens[pos].type != Token::RIGHT_PAREN) {
        Expression expr = First(tokens);
        list.push_back(expr);
      }
      // skip ')'
      pos++;
      return list;
    } else if (token.type == Token::NUMBER) {
      return *token.value.number;
    } else  // if(token.type == Token::SYMBOL)
    {
      Symbol* atom = new Symbol();
      return *token.value.symbol;
    }
    return nullptr;
  }

  Expression Second(Expression& expr) {
    if (expr.type == Expression::NUMBER || expr.type == Expression::SYMBOL) {
      return expr;
    } else if (expr.type == Expression::LIST) {
      List list = *expr.value.list;
      auto type = list[0].type;
      if (type == Expression::SYMBOL) {
        auto symbol = *list[0].value.symbol;
        if (symbol == "define") {
          // variable is the second
          Symbol variable(*list[1].value.symbol);
          // value is the third
          Expression value = Second(list[2]);
          return Definition(variable, value);
        } else if (symbol == "quote") {
          // quotes is the second
          Expression value = list[1];
          return Quotation(value);
        } else {
          // it's a procedure
          Symbol proc_name(symbol);
          // args
          List args;
          for (int i = 1; i < list.size(); i++) {
            args.push_back(Second(list[i]));
          }
          return Procedure(proc_name, args);
        }
      }
    }
    return nullptr;
  }
};
}  // namespace scxx
