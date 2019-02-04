#ifndef PARSER_H
#define PARSER_H

#include "../ast/expr/bin_expr.h"
#include "../ast/expr/expr.h"
#include "../ast/expr/grouping_expr.h"
#include "../ast/expr/literal_expr.h"
#include "../ast/expr/number_expr.h"
#include "../ast/expr/string_expr.h"
#include "../ast/expr/unary_expr.h"
#include "../ast/expr/var_expr.h"
#include "../ast/stmt/expr_stmt.h"
#include "../ast/stmt/var_stmt.h"
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

    Stmt* Statement();
    Stmt* Declaration();
    Stmt* VarDeclaration();
    Stmt* ExpressionStatement();

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
    std::vector<Stmt*> Parse();
};

#endif /* PARSER_H */
