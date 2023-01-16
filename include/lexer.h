#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "cv_string.h"
#include "type.h"

namespace scxx {

struct Token {
  enum Type { LEFT_PAREN, RIGHT_PAREN, SYMBOL, NUMBER } type;

  std::variant<Number, Symbol> value;

  Token(const Token& token) {
    switch (token.type) {
      case NUMBER:
        if (const Number* v = std::get_if<Number>(&token.value)) {
          type = NUMBER;
          value = *v;
        }
        break;
      case SYMBOL:
        if (const Symbol* v = std::get_if<Symbol>(&token.value)) {
          type = SYMBOL;
          value = *v;
        }
        break;
      default:
        type = token.type;
        break;
    }
  }

  Token(Token&& token) {
    switch (token.type) {
      case NUMBER:
        if (Number* v = std::get_if<Number>(&token.value)) {
          type = NUMBER;
          value = std::move(*v);
        }
        break;
      case SYMBOL:
        if (Symbol* v = std::get_if<Symbol>(&token.value)) {
          type = SYMBOL;
          value = std::move(*v);
        }
        break;
      default:
        type = token.type;
        break;
    }
  }

  Token(Type type) : type(type) {}
  Token(const Symbol& symbol) : type(SYMBOL) { value = symbol; }
  Token(const Number& number) : type(NUMBER) { value = number; }

  Token(Symbol&& symbol) : type(SYMBOL) { value = std::move(symbol); }
  Token(Number&& number) : type(NUMBER) { value = std::move(number); }

  friend std::ostream& operator<<(std::ostream& os, const Token& token) {
    switch (token.type) {
      case Token::LEFT_PAREN:
        os << "(";
        break;
      case Token::RIGHT_PAREN:
        os << ")";
        break;
      case Token::SYMBOL:
        std::visit([&os](auto&& arg) { os << "SYMBOL: " << arg; }, token.value);
        break;
      case Token::NUMBER:
        std::visit([&os](auto&& arg) { os << "NUMBER: " << arg; }, token.value);
        break;
      default:
        break;
    }
    return os;
  }
};

class Lexer {
 public:
  Lexer() {}

  /// @brief 进行词法分析，获取所有 tokens.
  /// @return 所有 tokens.
  std::vector<Token> Tokenize(std::string& source) {
    if (source == "") {
      return {};
    }
    // 1. split the source by whitespace
    cv_string::Replace(source, "(", " ( ");
    cv_string::Replace(source, ")", " ) ");
    cv_string::Replace(source, "'", " ' ");
    std::vector<std::string> ss = cv_string::Split(source, " ");

    bool quote = false;
    std::vector<Token> tokens{};

    std::for_each(ss.begin(), ss.end(),
                  [&tokens, &quote](const std::string& s) {
                    if (s == "(") {
                      tokens.push_back(Token::LEFT_PAREN);
                    } else if (s == ")") {
                      if (quote) {
                        tokens.push_back(Token::RIGHT_PAREN);
                        quote = false;
                      }
                      tokens.push_back(Token::RIGHT_PAREN);
                    } else if (s == "'") {
                      quote = true;
                      tokens.push_back(Token::LEFT_PAREN);
                      tokens.push_back(Symbol("quote"));
                    } else if (cv_string::IsNumber(s)) {
                      tokens.push_back(std::stod(s));
                    } else {
                      tokens.push_back(s);
                    }
                  });
    return tokens;
  }
};
}  // namespace scxx
