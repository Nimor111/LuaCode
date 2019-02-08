cmake_minimum_required(VERSION 3.12.4)
project(clua)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES src/error.cc src/scanner/scanner.cc src/scanner/token.cc src/ast/expr/bin_expr.cc src/ast/ast_printer.cc src/ast/expr/unary_expr.cc src/ast/expr/number_expr.cc src/ast/expr/string_expr.cc src/ast/expr/grouping_expr.cc src/ast/expr/literal_expr.cc src/ast/expr/var_expr.cc src/ast/parser/parser.cc src/ast/stmt/expr_stmt.cc src/ast/stmt/var_stmt.cc src/analyzer/rules.cc)
set(MAIN_FILE src/main.cc)
set(GLOB_RECURSE HEADER_FILES include/*.h)
set(TEST_FILES tests/setup.cc tests/scanner_test.cc tests/parser_test.cc tests/test_util.cc tests/analyzer_test.cc)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

find_package(Catch2 REQUIRED)
add_executable(tests ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES})

target_include_directories(tests PUBLIC include)
target_link_libraries(tests PUBLIC Catch2::Catch2)

find_package(nlohmann_json REQUIRED)

add_executable(clua ${SOURCE_FILES} ${HEADER_FILES} ${MAIN_FILE})
target_link_libraries(clua PUBLIC nlohmann_json)

target_include_directories(clua PUBLIC include)
