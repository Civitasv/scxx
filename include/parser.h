#pragma once

#include <vector>

#include "definition.h"
#include "error.h"
#include "expression.h"
#include "lexer.h"
#include "procedure.h"
#include "type.h"

namespace scxx {
class Parser {
 public:
  Expression* Parse(std::vector<Token*> tokens) {
    int pos = 0;
    return helper(tokens, &pos);
  }

 private:
  Expression* helper(std::vector<Token*> tokens, int* pos) {
    if (tokens.size() == *pos) {
      Error("Unexpected EOF");
    }
    Token* token = tokens[(*pos)++];
    if (token->type == Token::RIGHT_PAREN) {
      // if it is ')'
      Error("Syntax error: )");
    } else if (token->type == Token::LEFT_PAREN) {
      // if it is '(', go on until we met ')'
      Token::Type type = tokens[*pos]->type;
      if (type == Token::DEFINITION) {
        // 1. Definition
        // variable
        (*pos)++;
        Symbol* variable = tokens[*pos]->value.symbol;
        // value
        (*pos)++;
        Expression* value = helper(tokens, pos);
        return new Expression(new Definition(variable, value));
      } else if (type == Token::SYMBOL) {
        // Proc
        Symbol* proc_name = tokens[*pos]->value.symbol;
        (*pos)++;
        // args
        std::vector<Expression*> args;
        while (tokens[*pos]->type != Token::RIGHT_PAREN) {
          Expression* arg = helper(tokens, pos);
          args.push_back(arg);
        }
        return new Expression(new Procedure(proc_name, args));
      }
    } else if (token->type == Token::NUMBER) {
      Number* number = token->value.number;
      return new Expression(number);
    } else  // if(token.type == Token::SYMBOL)
    {
      Symbol* atom = token->value.symbol;
      return new Expression(atom);
    }
    return nullptr;
  }
};
}  // namespace scxx
