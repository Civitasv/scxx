#include <gtest/gtest.h>

#include <variant>

TEST(TEST, STD_VARIANT) {
  std::variant<std::unique_ptr<int>, float> v;

  auto index = v.index();
  std::cout << "index: " << index << '\n';
  auto p = std::get_if<std::unique_ptr<int>>(&v);
  if (*p != nullptr) {
    std::cout << "EXISTS!\n";
  } else {
    std::cout << "NOT!\n";
  }
}
