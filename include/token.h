#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

#include <any>
#include <string>
#include <variant>

using Literal = std::variant<std::string, double>;

enum TokenType {
    // single-char
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    POW,
    LEN,
    GT,
    LT,
    ASSIGN,
    SEMICOLON,
    COLON,
    COMMA,
    DOT,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_SQUARE,
    RIGHT_SQUARE,
    HYPHEN,

    // two-char
    EQ,     // ==
    DIFF,   // ~=
    GTE,    // >=
    LTE,    // <=
    CONCAT, // ..

    // three-char
    RANGE, // ...

    // Literals
    IDENT,
    STRING,
    NUMBER,

    // Keywords
    AND,
    BREAK,
    DO,
    ELSE,
    ELSEIF,
    END,
    FALSE,
    FOR,
    FUNCTION,
    IF,
    IN,
    LOCAL,
    NIL,
    NOT,
    OR,
    REPEAT,
    RETURN,
    THEN,
    TRUE,
    UNTIL,
    WHILE,

    T_EOF
};

class Token {
private:
    TokenType type_;
    std::string lexeme_;
    Literal literal_;
    int line_;

public:
    Token(TokenType type, std::string lexeme, Literal literal, int line);
    friend std::ostream& operator<<(std::ostream& os, Token const& token);
    bool operator==(Token const& other) const;
};

#endif /* TOKEN_H */
