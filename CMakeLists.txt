cmake_minimum_required(VERSION 3.20)
project(scheme_compiler)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(vendor/googletest)
