#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../include/catch.hpp"
#include "../include/scanner.h"

TEST_CASE("Scanner", "[scanner]")
{
    SECTION("Basic idents")
    {
        std::ifstream file("tests/fixtures/basic.lua");

        std::stringstream buffer;
        buffer << file.rdbuf();

        Scanner scanner(buffer.str());
        std::vector<Token> expectedTokens {
            Token(IDENT, "a", "", 2),
            Token(ASSIGN, "=", "", 2),
            Token(NUMBER, "5", 5, 2),
            Token(IDENT, "print", "", 4),
            Token(LEFT_PAREN, "(", "", 4),
            Token(IDENT, "a", "", 4),
            Token(RIGHT_PAREN, ")", "", 4),
            Token(T_EOF, "", "", 5)
        };

        auto tokens = scanner.ScanTokens();
        REQUIRE(tokens == expectedTokens);
    }

    SECTION("Operators")
    {
        std::ifstream file("tests/fixtures/operators.lua");

        std::stringstream buffer;
        buffer << file.rdbuf();

        Scanner scanner(buffer.str());

        std::vector<Token> expectedTokens {
            Token(NUMBER, "1", 1, 1),
            Token(PLUS, "+", "", 1),
            Token(NUMBER, "2", 2, 1),
            Token(NUMBER, "1", 1, 2),
            Token(MINUS, "-", "", 2),
            Token(NUMBER, "2", 2, 2),
            Token(NUMBER, "1", 1, 3),
            Token(MUL, "*", "", 3),
            Token(NUMBER, "2", 2, 3),
            Token(NUMBER, "1", 1, 4),
            Token(DIV, "/", "", 4),
            Token(NUMBER, "2", 2, 4),
            Token(NUMBER, "1", 1, 5),
            Token(MOD, "%", "", 5),
            Token(NUMBER, "2", 2, 5),
            Token(NUMBER, "1", 1, 6),
            Token(POW, "^", "", 6),
            Token(NUMBER, "2", 2, 6),
            Token(NUMBER, "1", 1, 7),
            Token(BIT_AND, "&", "", 7),
            Token(NUMBER, "2", 2, 7),
            Token(NUMBER, "1", 1, 8),
            Token(BIT_OR, "|", "", 8),
            Token(NUMBER, "2", 2, 8),
            Token(NUMBER, "1", 1, 9),
            Token(BIT_XOR, "~", "", 9),
            Token(NUMBER, "2", 2, 9),
            Token(NUMBER, "1", 1, 10),
            Token(GT, ">", "", 10),
            Token(NUMBER, "2", 2, 10),
            Token(NUMBER, "1", 1, 11),
            Token(LT, "<", "", 11),
            Token(NUMBER, "2", 2, 11),
            Token(NUMBER, "1", 1, 12),
            Token(ASSIGN, "=", "", 12),
            Token(NUMBER, "2", 2, 12),
            Token(SEMICOLON, ";", "", 12),
            Token(T_EOF, "", "", 13)
        };

        auto tokens = scanner.ScanTokens();
        REQUIRE(tokens == expectedTokens);
    }

    SECTION("Function definition")
    {
        std::ifstream file("tests/fixtures/function.lua");

        std::stringstream buffer;
        buffer << file.rdbuf();

        Scanner scanner(buffer.str());

        std::vector<Token> expectedTokens {
            Token(FUNCTION, "function", "", 1),
            Token(IDENT, "sum", "", 1),
            Token(LEFT_PAREN, "(", "", 1),
            Token(IDENT, "a", "", 1),
            Token(COMMA, ",", "", 1),
            Token(IDENT, "b", "", 1),
            Token(RIGHT_PAREN, ")", "", 1),
            Token(RETURN, "return", "", 2),
            Token(IDENT, "a", "", 2),
            Token(PLUS, "+", "", 2),
            Token(IDENT, "b", "", 2),
            Token(END, "end", "", 3),
            Token(T_EOF, "", "", 4)
        };

        auto tokens = scanner.ScanTokens();
        REQUIRE(tokens == expectedTokens);
    }
}
