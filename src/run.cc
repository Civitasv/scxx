#include <iostream>

#include "cxxopts/cxxopts.hpp"

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

  std::cout << options.help() << std::endl;
}

int main(int argc, const char** argv) {
  parse(argc, argv);

  return 0;
}