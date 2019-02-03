#ifndef PARSER_H
#define PARSER_H

#include "../ast/bin_expr.h"
#include "../ast/expr.h"
#include "../ast/grouping_expr.h"
#include "../ast/number_expr.h"
#include "../ast/string_expr.h"
#include "../ast/unary_expr.h"
#include "../error.h"
#include "../errors/parse_error.h"
#include "../scanner/token.h"
#include <vector>

/**
Operator precedence is as follows:
    or
    and
    <     >     <=    >=    ~=    ==
    |
    ~
    &
    <<    >>
    ..
    +     -
    *     /     //    %
    unary operators (not   #     -     ~)
    ^
*/

class Parser {
private:
    std::vector<Token> tokens_;
    int at_;

    Expr* Expression();
    Expr* Or();
    Expr* And();
    Expr* Comparison();
    Expr* BitOr();
    Expr* BitXor();
    Expr* BitAnd();
    Expr* Shift();
    Expr* Concat();
    Expr* AddSub();
    Expr* MulDivMod();
    Expr* Unary();
    Expr* Pow();
    Expr* Primary();

    bool Match(std::vector<TokenType> const&);
    Token Previous();
    Token Advance();
    bool Check(TokenType);
    bool End();
    Token Peek();
    Token Consume(TokenType, std::string);
    ParseError Error(Token, std::string);
    void Synchronize();

public:
    Parser(std::vector<Token>);
    Expr* Parse();
};

#endif /* PARSER_H */
