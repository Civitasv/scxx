#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "cv_string.h"
#include "type.h"

namespace scxx {

struct Token {
  enum Type { LEFT_PAREN, RIGHT_PAREN, SYMBOL, NUMBER, DEFINITION };
  union Value {
    Number* number;
    Symbol* symbol;
  };

  Token(Type type) : type(type) {}
  Token(Symbol* symbol) : type(SYMBOL) { value.symbol = symbol; }
  Token(Number* number) : type(NUMBER) { value.number = number; }

  ~Token() {
    if (type == SYMBOL) {
      if (value.symbol) delete value.symbol;
    } else if (type == NUMBER) {
      if (value.number) delete value.number;
    }
  }

  Type type;
  Value value;

  friend std::ostream& operator<<(std::ostream& os, const Token& token) {
    switch (token.type) {
      case Token::LEFT_PAREN:
        os << "(";
        break;
      case Token::RIGHT_PAREN:
        os << ")";
        break;
      case Token::SYMBOL:
        os << "SYMBOL: " << *token.value.symbol;
        break;
      case Token::NUMBER:
        os << "NUMBER: " << *token.value.number;
        break;
      case Token::DEFINITION:
        os << "DEFINE";
        break;
      default:
        break;
    }
    return os;
  }
};

class Lexer {
 public:
  Lexer(const std::string& source) : source(source) {}

  /// @brief 进行词法分析，获取所有 tokens.
  /// @return 所有 tokens.
  std::vector<Token*> Tokenize() {
    // 1. split the source by whitespace
    cv_string::Replace(source, "(", " ( ");
    cv_string::Replace(source, ")", " ) ");
    std::vector<std::string> ss = cv_string::Split(source, " ");

    std::vector<Token*> tokens{};

    std::for_each(ss.begin(), ss.end(), [&tokens](const std::string& s) {
      if (s == "(") {
        tokens.push_back(new Token(Token::LEFT_PAREN));
      } else if (s == ")") {
        tokens.push_back(new Token(Token::RIGHT_PAREN));
      } else if (s == "define") {
        tokens.push_back(new Token(Token::DEFINITION));
      } else if (cv_string::IsNumber(s)) {
        tokens.push_back(new Token(new Number(std::stod(s))));
      } else {
        tokens.push_back(new Token(new Symbol(s)));
      }
    });
    return tokens;
  }

 private:
  std::string source;
};
}  // namespace scxx
