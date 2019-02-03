#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../include/ast/ast_printer.h"
#include "../include/catch.hpp"
#include "../include/parser/parser.h"
#include "../include/scanner/scanner.h"
#include "test_util.cc"

TEST_CASE("Parser", "[parser]")
{
    SECTION("Expression")
    {
        auto contents = readFixture("tests/fixtures/expr.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto expr = parser.Parse();

        std::stringstream buff;
        auto* old = std::cout.rdbuf(buff.rdbuf());

        auto astPrinter = AstPrinter();
        astPrinter.Print(expr);

        CHECK(buff.str() == "(- (+ (1.000000) (2.000000)) (* (3.000000) (4.000000)))");

        // reset std::cout
        std::cout.rdbuf(old);
    }

    SECTION("Booleans and nil")
    {
        auto contents = readFixture("tests/fixtures/boolnil.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto expr = parser.Parse();

        std::stringstream buff;
        auto* old = std::cout.rdbuf(buff.rdbuf());

        auto astPrinter = AstPrinter();
        astPrinter.Print(expr);

        CHECK(buff.str() == "(and (and (true) (false)) (nil))");

        // reset std::cout
        std::cout.rdbuf(old);
    }
}
