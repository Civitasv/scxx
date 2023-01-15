add_library(
  interpreter
  definition.cc
  environment.cc
  eval.cc
  expression.cc
  call.cc
  condition.cc
  primitive.cc
  procedure.cc
  quotation.cc)

target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/vendor
                                              ${CMAKE_SOURCE_DIR}/include)

add_executable(run run.cc)

target_link_libraries(run PUBLIC interpreter fmt)

target_include_directories(run PUBLIC ${CMAKE_SOURCE_DIR}/vendor
                                      ${CMAKE_SOURCE_DIR}/include)
