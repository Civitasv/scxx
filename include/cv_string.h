/**
 * This is a single-header library. Followed by:
 * https://github.com/nothings/stb/blob/master/docs/stb_howto.txt To use it:
 *
 * To use this library:
 * 1. #define CV_STRING_IMPLENTATION
 * 2. #include "cv_string.h"
 */

#ifndef CVI_INCLUDE_CV_STRING_H
#define CVI_INCLUDE_CV_STRING_H

#include <cctype>
#include <regex>
#include <string>
#include <vector>

namespace cv_string {
void Replace(std::string& source, const std::string& from,
             const std::string& to);

std::vector<std::string> Split(const std::string& source,
                               const std::string& delimiter);

bool IsNumber(const std::string& str);
}  // namespace cv_string
#endif

#ifdef CV_STRING_IMPLENTATION
namespace cv_string {
const std::regex NUMBER_REGEX("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$");

// From https://stackoverflow.com/a/24315631/11112422
void Replace(std::string& source, const std::string& from,
             const std::string& to) {
  size_t start_pos = 0;

  while ((start_pos = source.find(from, start_pos)) != std::string::npos) {
    source.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

std::vector<std::string> Split(const std::string& source,
                               const std::string& delimiter) {
  std::vector<std::string> ss;
  size_t pos = 0, last = 0;
  std::string token;
  while ((pos = source.find(delimiter, last)) != std::string::npos) {
    token = source.substr(last, pos - last);
    if (token.size() > 0) ss.push_back(std::move(token));
    last = pos + delimiter.length();
  }

  if (last < source.size()) ss.push_back(source.substr(last));

  return ss;
}

bool IsNumber(const std::string& str) {
  std::smatch match;

  return std::regex_match(str, match, NUMBER_REGEX);
}

}  // namespace cv_string
#endif
