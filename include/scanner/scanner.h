#ifndef SCANNER_H
#define SCANNER_H

#include "error.h"
#include "token.h"
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Scanner {
private:
    static std::map<std::string, TokenType> keywords_;

    std::string source_;
    std::vector<Token> tokens_;

    int start_;
    int current_;
    int line_;

    bool End(int = 0);
    void ScanToken();
    char Advance();
    void AddToken(TokenType);
    void AddToken(TokenType, Literal);
    bool Match(char);
    std::string Peek(int = 0);
    void String(bool);
    void MultiString();
    void Number();
    bool Alpha(char c);
    void Identifier();
    void MultiComment();
    void Comment();

public:
    Scanner(std::string);
    std::vector<Token> ScanTokens();
};

#endif /* SCANNER_H */
