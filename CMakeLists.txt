cmake_minimum_required(VERSION 3.20)
project(scheme_compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(vendor/googletest)
add_subdirectory(vendor/fmt)
