#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "approval/ApprovalTests.hpp"
#include "cv_string.h"
#include "lexer.h"
#include "parser.h"

using namespace scxx;

using namespace ApprovalTests;

TEST(SCXX, LEX_1) {
  std::string source = "(+ (+ 1 2) 2)";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  // auto converter = [](auto s, auto& os) { os << s << " => " << s[0]; };
  Approvals::verifyAll("TOKENS", tokens);
}

TEST(SCXX, PARSER_1) {
  std::string source = "(+ (+ 1 2) 2)";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);

  Approvals::verify(expr);
}

TEST(SCXX, PARSER_2) {
  std::string source = "(define q (+ 1 2))";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);
  
  Approvals::verify(expr);
}

TEST(SCXX, PARSER_3) {
  std::string source = "(define q (+ 1 (+ 1 2)))";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);

  Approvals::verify(expr);
}

TEST(SCXX, PARSER_4) {
  std::string source = "(quote 1)";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);

  Approvals::verify(expr);
}

TEST(SCXX, PARSER_5) {
  std::string source = "(quote (1 2))";
  Lexer lexer;
  auto tokens = lexer.Tokenize(source);
  Parser parser;

  Expression expr = parser.Parse(tokens);

  Approvals::verify(expr);
}
