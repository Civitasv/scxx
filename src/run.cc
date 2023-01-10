#include <iostream>

#include "cxxopts/cxxopts.hpp"
#include "environment.h"
#include "eval.h"
#include "lexer.h"
#include "parser.h"
#include "primitive.h"

#define CV_STRING_IMPLENTATION
#include "cv_string.h"

std::string read() {
  std::string source;
  getline(std::cin, source);
  return source;
}

void print(const std::string& message) { std::cout << message; }

void repl() {
  using namespace scxx;
  Environment* environment = StandardEnv();
  Lexer lexer;
  Parser parser;
  // read, eval, print, loop
  while (true) {
    print("1 ]=> ");
    std::string input = read();
    std::vector<Token> tokens = lexer.Tokenize(input);
    Expression expr = parser.Parse(tokens);
    Expression output = Eval(expr, environment);
    std::cout << ";Value: " << output;
    print("\n");
  }
  delete environment;
}

void parse(int argc, const char* argv[]) {
  cxxopts::Options options(argv[0], "Scheme Compiler in C++");

  // clang-format off
  options.add_options()
    ("f,file", "scheme file path", cxxopts::value<std::string>())
    ("h,help", "Print usage");
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (result.count("file")) {
    auto filepath = result["file"].as<std::string>();
    std::cout << "FILE PATH: " << filepath << '\n';
    exit(0);
  }

  repl();
}

int main(int argc, const char** argv) {
  parse(argc, argv);

  return 0;
}
