#pragma once

#include <vector>

#include "definition.h"
#include "error.h"
#include "expression.h"
#include "lexer.h"
#include "type.h"

namespace scxx {
class Parser {
 public:
  Expression Parse(std::vector<Token*> tokens) {
    int pos = 0;
    return helper(tokens, pos, false);
  }

 private:
  Expression helper(std::vector<Token*> tokens, int& pos, bool quote) {
    if (tokens.size() == pos) {
      Error("Unexpected EOF");
    }
    Token* token = tokens[pos++];
    if (token->type == Token::RIGHT_PAREN) {
      // if it is ')'
      Error("Syntax error: )");
    } else if (token->type == Token::LEFT_PAREN) {
      // if it is '(', go on until we met ')'
      Token::Type type = tokens[pos]->type;
      if (quote) {
        // 如果在 quote 下，那么直接读取 list
        List list;
        while (tokens[pos]->type != Token::RIGHT_PAREN) {
          Expression expr = helper(tokens, pos, quote);
          list.push_back(expr);
        }
        // skip ')'
        pos++;
        return list;
      } else {
        if (type == Token::DEFINITION) {
          // 1. Definition, (define x (+ 1 2))
          // variable
          pos++;
          Symbol variable(*tokens[pos]->value.symbol);
          // value
          pos++;
          Expression value = helper(tokens, pos, false);
          return Definition(variable, value);
        } else if (type == Token::QUOTATION) {
          // 2. Quotation, (quote (x 1 2))
          pos++;
          Expression quote = helper(tokens, pos, true);
          return Quotation(quote);
        } else if (type == Token::SYMBOL) {
          // Then it must be normal procedure
          // Proc
          Symbol proc_name(*tokens[pos]->value.symbol);
          pos++;
          // args
          List args;
          while (tokens[pos]->type != Token::RIGHT_PAREN) {
            Expression arg =
                helper(tokens, pos, false);  // TODO, 这里应该变成 右值移动
            args.push_back(arg);
          }
          // skip ')'
          pos++;
          return Procedure(proc_name, args);
        }
      }
    } else if (token->type == Token::NUMBER) {
      return *token->value.number;
    } else  // if(token.type == Token::SYMBOL)
    {
      Symbol* atom = new Symbol();
      return *token->value.symbol;
    }
    return nullptr;
  }
};
}  // namespace scxx
