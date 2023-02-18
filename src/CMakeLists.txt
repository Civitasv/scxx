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
target_link_libraries(interpreter PUBLIC fmt)

# for llvm
find_package(LLVM REQUIRED CONFIG)
message(STATUS "FOUND LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

target_include_directories(interpreter PUBLIC ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(interpreter PUBLIC ${llvm_libs})

# for runner
add_executable(run run.cc)

target_link_libraries(run PUBLIC interpreter)

target_include_directories(run PUBLIC ${CMAKE_SOURCE_DIR}/vendor
                                      ${CMAKE_SOURCE_DIR}/include)
