add_executable(run run.cc)

target_include_directories(run PUBLIC ${CMAKE_SOURCE_DIR}/vendor
                                      ${CMAKE_SOURCE_DIR}/include)
