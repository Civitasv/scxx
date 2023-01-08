#include <gtest/gtest.h>

#include <iostream>

#include "lexer.h"
#include "parser.h"

#define CV_STRING_IMPLENTATION
#include "cv_string.h"

using namespace scxx;

TEST(SCXX, LEX_1) {
  auto source = "(+ (+ 1 2) 2)";
  Lexer lexer(source);
  auto tokens = lexer.Tokenize();

  std::cout << "TOKENS: " << '\n';
  for (auto& token : tokens) {
    std::cout << *token << '\n';
  }
  std::cout << '\n';
  for (auto& token : tokens) delete token;
  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_1) {
  auto source = "(+ (+ 1 2) 2)";
  Lexer lexer(source);
  auto tokens = lexer.Tokenize();
  Parser parser;

  Expression* expr = parser.Parse(tokens);
  std::cout << *expr << '\n';

  for (auto& token : tokens) delete token;
  delete expr;
  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_2) {
  auto source = "(define q (+ 1 2))";
  Lexer lexer(source);
  auto tokens = lexer.Tokenize();
  Parser parser;

  Expression* expr = parser.Parse(tokens);
  std::cout << *expr << '\n';

  for (auto& token : tokens) delete token;
  delete expr;
  EXPECT_EQ(1, 1);
}
