#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../include/analyzer/rules.h"
#include "../include/ast/ast_printer.h"
#include "../include/catch.hpp"
#include "../include/parser/parser.h"
#include "../include/scanner/scanner.h"
#include "test_util.cc"

TEST_CASE("Analyzer", "[analyzer]")
{
    SECTION("Undefined variables")
    {
        auto contents = readFixture("tests/fixtures/undefined.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto stmts = parser.Parse();

        auto errors = UndefinedVariables(stmts);

        REQUIRE(errors == std::vector<std::string> { "b not declared!" });
    }

    SECTION("Unused variables")
    {
        auto contents = readFixture("tests/fixtures/unused.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto stmts = parser.Parse();

        auto errors = UnusedVariables(stmts);

        REQUIRE(errors == std::vector<std::string> { "a not used!" });
    }
}
