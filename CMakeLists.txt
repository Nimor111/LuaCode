cmake_minimum_required(VERSION 3.12.4)
project(clua)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES src/error.cc src/scanner.cc src/token.cc src/ast/bin_expr.cc src/ast/ast_printer.cc src/ast/unary_expr.cc src/ast/number_expr.cc src/ast/visitor.cc)
set(MAIN_FILE src/main.cc)
set(GLOB_RECURSE HEADER_FILES include/*.h)
set(TEST_FILES tests/setup.cc tests/scanner_test.cc)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

find_package(Catch2 REQUIRED)
add_executable(tests ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES})

target_include_directories(tests PUBLIC include)
target_link_libraries(tests Catch2::Catch2)

add_executable(clua ${SOURCE_FILES} ${HEADER_FILES} ${MAIN_FILE})

target_include_directories(clua PUBLIC include)

