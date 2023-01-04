enable_testing()
include(GoogleTest)

add_executable(test test.cc)

target_link_libraries(test PUBLIC gtest_main)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include)

gtest_discover_tests(test)
