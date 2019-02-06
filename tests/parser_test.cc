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
    SECTION("Expressions")
    {
        auto contents = readFixture("tests/fixtures/expr.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto exprs = parser.Parse();

        std::stringstream buff;
        auto* old = std::cout.rdbuf(buff.rdbuf());

        auto astPrinter = AstPrinter();
        astPrinter.Print(exprs[0]);

        std::string expected = "{\"type\": \"BinaryExpression\", \"operator\": \"-\", \"args\": [{\"type\": \"BinaryExpression\", \"operator\": \"+\", \"args\": [{\"type\": \"NumberLiteral\", \"value\": 1}, {\"type\": \"NumberLiteral\", \"value\": 2}]}, {\"type\": \"BinaryExpression\", \"operator\": \"*\", \"args\": [{\"type\": \"NumberLiteral\", \"value\": 3}, {\"type\": \"NumberLiteral\", \"value\": 4}]}]}";
        CHECK(buff.str() == expected);

        // reset std::cout
        std::cout.rdbuf(old);
    }

    SECTION("Booleans and nil")
    {
        auto contents = readFixture("tests/fixtures/boolnil.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto exprs = parser.Parse();

        std::stringstream buff;
        auto* old = std::cout.rdbuf(buff.rdbuf());

        auto astPrinter = AstPrinter();
        astPrinter.Print(exprs[0]);

        std::string expected = "{\"type\": \"BinaryExpression\", \"operator\": \"and\", \"args\": [{\"type\": \"BinaryExpression\", \"operator\": \"and\", \"args\": [{\"type\": \"KeyLiteral\", \"value\": \"true\"}, {\"type\": \"KeyLiteral\", \"value\": \"false\"}]}, {\"type\": \"KeyLiteral\", \"value\": \"nil\"}]}";
        CHECK(buff.str() == expected);

        // reset std::cout
        std::cout.rdbuf(old);
    }

    SECTION("Variables")
    {
        auto contents = readFixture("tests/fixtures/var.lua");

        Scanner scanner(contents);
        auto tokens = scanner.ScanTokens();

        Parser parser(tokens);
        auto exprs = parser.Parse();

        std::stringstream buff;
        auto* old = std::cout.rdbuf(buff.rdbuf());

        auto astPrinter = AstPrinter();
        astPrinter.Print(exprs[0]);

        std::string expected = "{\"type\": \"VarDeclaration\", \"name\": \"a\", \"value\": {\"type\": \"BinaryExpression\", \"operator\": \"*\", \"args\": [{\"type\": \"NumberLiteral\", \"value\": 5}, {\"type\": \"NumberLiteral\", \"value\": 6}]}}";
        CHECK(buff.str() == expected);

        buff = std::stringstream();
        astPrinter.Print(exprs[1]);

        expected = "{\"type\": \"VarDeclaration\", \"name\": \"b\", \"value\": {\"type\": \"BinaryExpression\", \"operator\": \"+\", \"args\": [{\"type\": \"NumberLiteral\", \"value\": 6}, {\"type\": \"BinaryExpression\", \"operator\": \"*\", \"args\": [{\"type\": \"NumberLiteral\", \"value\": 7}, {\"type\": \"NumberLiteral\", \"value\": 3}]}]}}";
        CHECK(buff.str() == expected);

        buff = std::stringstream();
        astPrinter.Print(exprs[2]);

        expected = "{\"type\": \"VarDeclaration\", \"name\": \"c\", \"value\": {\"type\": \"BinaryExpression\", \"operator\": \"and\", \"args\": [{\"type\": \"KeyLiteral\", \"value\": \"true\"}, {\"type\": \"KeyLiteral\", \"value\": \"false\"}]}}";
        CHECK(buff.str() == expected);

        // reset std::cout
        std::cout.rdbuf(old);
    }
}
