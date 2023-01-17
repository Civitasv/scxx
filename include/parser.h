#pragma once

#include <iostream>
#include <vector>

#include "definition.h"
#include "error.h"
#include "expression.h"
#include "fmt/core.h"
#include "lexer.h"
#include "type.h"

namespace scxx {
class Parser {
 private:
  int pos;
  bool quotation;

 public:
  Expression Parse(std::vector<Token>& tokens) {
    pos = 0;
    quotation = false;
    Expression expr = ResolveTokens(tokens);
    Expression result = ExtractList(expr);
    return result;
  }

 private:
  /// @brief
  /// 将 tokens 解析为 Call 和 Atom(Symbol & Number)
  /// @param tokens
  /// @return Expression
  Expression ResolveTokens(std::vector<Token>& tokens) {
    if (tokens.size() == pos) {
      panic("Unexpected EOF");
    }
    Token token = tokens[pos++];
    if (token.type == Token::RIGHT_PAREN) {
      // if it is ')'
      panic(fmt::format("Syntax error: {}", ')'));
    } else if (token.type == Token::LEFT_PAREN) {  // Expression
      // if it is '(', go on until we met ')'
      List list;
      while (tokens[pos].type != Token::RIGHT_PAREN) {
        Expression expr = ResolveTokens(tokens);
        list.push_back(expr);
      }
      // skip ')'
      pos++;
      return list;
    } else if (token.type == Token::NUMBER) {
      return *std::get<std::unique_ptr<Number>>(token.value);
    } else  // if(token.type == Token::SYMBOL)
    {
      return *std::get<std::unique_ptr<Symbol>>(token.value);
    }
    return {};
  }

  /// @brief
  /// 将 List 进一步解析为
  /// Special(if, define, quotation, lambda)
  /// 和 Call(Primitive 和 Procedure)
  /// @param expr
  /// @return Expression
  Expression ExtractList(Expression& expr) {
    if (expr.type == Expression::NUMBER || expr.type == Expression::SYMBOL) {
      return expr;
    } else if (expr.type == Expression::LIST) {
      List list = *expr.AsList();
      // What if it is empty, like (), then return an empty list
      if (list.empty()) {
        return Quotation(List{});
      }

      auto type = list[0].type;
      if (type == Expression::LIST) {
        // it should be ((lambda (x) x) 2)
        Expression prc = ExtractList(list[0]);
        if (prc.type != Expression::LAMBDA) {
          panic(fmt::format("illed form of expression: {}", expr.Dump()));
        }
        // args
        List args;
        for (int i = 1; i < list.size(); i++) {
          args.push_back(ExtractList(list[i]));
        }
        return Call(prc, args);
      }
      if (type != Expression::SYMBOL) {
        panic(fmt::format("it should be a symbol: {}", list[0].Dump()));
      }
      auto symbol = *list[0].AsSymbol();

      if (symbol == "if") {
        // (if (> 2 1) (* x x) (* x 2))
        if (list.size() < 4) {
          panic(fmt::format("illed form of if: {}", expr.Dump()));
        }
        Expression predicate = ExtractList(list[1]);
        Expression consequent = ExtractList(list[2]);
        Expression alternative = ExtractList(list[3]);
        return Condition(predicate, consequent, alternative);
      } else if (symbol == "define") {
        // (define symbol expression)
        if (list.size() < 3) {
          panic(fmt::format("illed form of define: {}", expr.Dump()));
        }
        Symbol variable(*list[1].AsSymbol());
        Expression value = ExtractList(list[2]);
        return Definition(variable, value);
      } else if (symbol == "quote") {
        // (quote expression)
        if (list.size() < 2) {
          panic(fmt::format("illed form of quotation: {}", expr.Dump()));
        }
        Expression value = list[1];
        return Quotation(value);
      } else if (symbol == "lambda") {
        // (lambda (p1 p2 p3) expr1 expr2 ...)
        // parameters
        if (list.size() < 3) {
          panic(fmt::format("illed form of lambda: {}", expr.Dump()));
        }
        Expression expr1 = list[1];
        if (expr1.type != Expression::LIST) {
          panic(fmt::format("illed form of lambda: {}", expr.Dump()));
        }
        std::vector<Symbol> parameters;
        for (auto& item : *expr1.AsList()) {
          parameters.push_back(*item.AsSymbol());
        }
        // body
        List body;
        for (int i = 2; i < list.size(); i++) {
          body.push_back(ExtractList(list[i]));
        }
        // then make a procedure
        return Procedure(parameters, body);
      } else {
        // then it must be a call
        Symbol proc_name(symbol);
        // args
        List args;
        for (int i = 1; i < list.size(); i++) {
          args.push_back(ExtractList(list[i]));
        }

        return Call(proc_name, args);
      }
    }
    return {};
  }
};
}  // namespace scxx
