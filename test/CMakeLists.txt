enable_testing()
include(GoogleTest)

add_executable(test test.cc main.cc)
add_executable(test_cv_string test_cv_string.cc)
add_executable(test_std_variant test_std_variant.cc)

target_link_libraries(test PUBLIC gtest gtest_main interpreter)
target_link_libraries(test_cv_string PUBLIC gtest gtest_main gmock_main
                                            interpreter)
target_link_libraries(test_std_variant PUBLIC gtest gtest_main)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cv_string PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_std_variant PUBLIC ${CMAKE_SOURCE_DIR}/include)

gtest_discover_tests(test)
gtest_discover_tests(test_cv_string)
gtest_discover_tests(test_std_variant)
