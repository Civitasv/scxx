#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <string>

#define CV_STRING_IMPLENTATION
#include "cv_string.h"

using namespace cv_string;

TEST(CV_STRING, E_1) {
  std::string source = "(+ 1 2)";
  Replace(source, "(", " ( ");

  EXPECT_EQ(source, " ( + 1 2)");
}

TEST(CV_STRING, E_2) {
  std::string source = "a,b,c";
  auto result = Split(source, ",");

  ASSERT_THAT(result, testing::ElementsAre("a", "b", "c"));
}

