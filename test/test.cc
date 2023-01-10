#include <gtest/gtest.h>

#include <iostream>

#include "lexer.h"
#include "parser.h"

#define CV_STRING_IMPLENTATION
#include "cv_string.h"

using namespace scxx;

TEST(SCXX, LEX_1) {
  std::string source = "(+ (+ 1 2) 2)";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);

  std::cout << "TOKENS: " << '\n';
  for (auto& token : tokens) {
    std::cout << token << '\n';
  }
  std::cout << '\n';
  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_1) {
  std::string source = "(+ (+ 1 2) 2)";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);
  std::cout << expr << '\n';

  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_2) {
  std::string source = "(define q (+ 1 2))";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);
  std::cout << expr << '\n';

  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_3) {
  std::string source = "(define q (+ 1 (+ 1 2)))";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);
  std::cout << expr << '\n';

  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_4) {
  std::string source = "(quote 1)";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);
  std::cout << expr << '\n';

  EXPECT_EQ(1, 1);
}

TEST(SCXX, PARSER_5) {
  std::string source = "(quote (1 2))";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);
  std::cout << expr << '\n';

  EXPECT_EQ(1, 1);
}
