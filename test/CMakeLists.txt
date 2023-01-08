enable_testing()
include(GoogleTest)

add_executable(test test.cc)
add_executable(test_cv_string test_cv_string.cc)

target_link_libraries(test PUBLIC gtest_main gmock_main interpreter)
target_link_libraries(test_cv_string PUBLIC gtest_main gmock_main interpreter)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cv_string PUBLIC ${CMAKE_SOURCE_DIR}/include)

gtest_discover_tests(test)
gtest_discover_tests(test_cv_string)
