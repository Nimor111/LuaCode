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
}
