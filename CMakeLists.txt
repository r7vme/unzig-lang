cmake_minimum_required(VERSION 3.10)
project(unzig)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# LLVM
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(src)

add_library(unzig_lib
  src/ast.cpp
  src/parser.cpp
  src/codegen.cpp
  src/dotgen.cpp
  src/tokenizer.cpp
  src/types.cpp
  src/sema.cpp
  src/scope.cpp
  src/source.cpp
)
target_link_libraries(unzig_lib PRIVATE LLVM)

add_executable(unzig src/unzig_cmd.cpp)
target_link_libraries(unzig unzig_lib)

# tests
add_subdirectory(third_party/Catch2)
add_executable(tests
  test/test_tokenizer.cpp
  test/test_parser.cpp
  test/test_codegen.cpp
  test/test_sema.cpp
  test/test_scope.cpp
  test/test_dotgen.cpp
  test/test_source.cpp
)
target_link_libraries(tests PRIVATE unzig_lib Catch2::Catch2WithMain)
