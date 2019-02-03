#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../include/ast/ast_printer.h"
#include "../include/catch.hpp"
#include "../include/parser/parser.h"
#include "../include/scanner/scanner.h"

TEST_CASE("Parser", "[parser]")
{
    SECTION("Expression")
    {
        std::ifstream file("tests/fixtures/expr.lua");

        std::stringstream buffer;
        buffer << file.rdbuf();

        Scanner scanner(buffer.str());
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
}
