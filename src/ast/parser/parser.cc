#include "../../../include/parser/parser.h"

Parser::Parser(std::vector<Token> tokens)
    : tokens_(tokens)
    , at_(0)
{
}

std::vector<Stmt*> Parser::Parse()
{
    try {
        std::vector<Stmt*> statements;
        while (!End()) {
            statements.push_back(Statement());
        }

        return statements;
    } catch (ParseError const& e) {
        return std::vector<Stmt*>();
    }
}

Stmt* Parser::Statement()
{
    return ExpressionStatement();
}

Stmt* Parser::ExpressionStatement()
{
    auto expr = Expression();

    auto s = new ExprStmt(expr);

    return s;
}

Expr* Parser::Expression()
{
    return Or();
}

Expr* Parser::Or()
{
    auto expr = And();
    std::vector<TokenType> tokens = { AND };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = And();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::And()
{
    auto expr = Comparison();
    std::vector<TokenType> tokens = { LT, GT, LTE, GTE, DIFF, EQ };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = Comparison();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::Comparison()
{
    auto expr = BitOr();

    std::vector<TokenType> tokens = { BIT_OR };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = BitOr();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::BitOr()
{
    auto expr = BitAnd();

    std::vector<TokenType> tokens = { BIT_AND };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = BitAnd();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::BitAnd()
{
    auto expr = Shift();

    std::vector<TokenType> tokens = { BIT_AND };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = Shift();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::Shift()
{
    auto expr = Concat();

    std::vector<TokenType> tokens = { LEFT_SHIFT, RIGHT_SHIFT };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = Concat();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::Concat()
{
    auto expr = AddSub();

    std::vector<TokenType> tokens = { CONCAT };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = AddSub();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::AddSub()
{
    auto expr = MulDivMod();

    std::vector<TokenType> tokens = { PLUS, MINUS };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = MulDivMod();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::MulDivMod()
{
    auto expr = Unary();

    std::vector<TokenType> tokens = { MUL, DIV, FLOOR_DIV, MOD };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = Unary();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::Unary()
{
    // TODO scanner handle minus
    std::vector<TokenType> tokens = { NOT, LEN };

    if (Match(tokens)) {
        auto op = Previous();
        auto right = Pow();
        auto u = new UnaryExpr(op, right);
        return u;
    }

    return Primary();
}

Expr* Parser::Pow()
{
    auto expr = Primary();

    std::vector<TokenType> tokens = { POW };

    while (Match(tokens)) {
        auto op = Previous();
        auto right = Primary();
        expr = new BinExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::Primary()
{
    std::vector<TokenType> tokens = { FALSE };
    if (Match(tokens)) {
        auto e = new LiteralExpr(0);
        return e;
    }

    tokens = { TRUE };
    if (Match(tokens)) {
        auto e = new LiteralExpr(1);
        return e;
    }

    tokens = { NIL };
    if (Match(tokens)) {
        auto e = new LiteralExpr(-1);
        return e;
    }

    tokens = { NUMBER };
    if (Match(tokens)) {
        auto e = new NumberExpr(std::get<double>(Previous().literal()));
        return e;
    }

    tokens = { STRING };

    if (Match(tokens)) {
        auto e = new StringExpr(std::get<std::string>(Previous().literal()));
        return e;
    }

    tokens = { LEFT_PAREN };

    if (Match(tokens)) {
        auto e = Expression();
        Consume(RIGHT_PAREN, "Expect ')' after expression.");
        auto ge = new GroupingExpr(e);
        return ge;
    }

    throw Error(Peek(), "Expected expression.");
}

bool Parser::Match(std::vector<TokenType> const& tokens)
{
    for (auto const& tt : tokens) {
        // check if current token is any of the given types
        if (Check(tt)) {
            Advance();
            return true;
        }
    }

    return false;
}

bool Parser::Check(TokenType type)
{
    if (End()) {
        return false;
    }

    return Peek().type() == type;
}

Token Parser::Advance()
{
    if (!End()) {
        this->at_++;
    }

    return Previous();
}

bool Parser::End()
{
    return Peek().type() == T_EOF;
}

Token Parser::Peek()
{
    if (this->at_ < this->tokens_.size()) {
        return this->tokens_[this->at_];
    }

    return Token(T_EOF, "", "", 0);
}

Token Parser::Previous()
{
    if (this->at_ < this->tokens_.size()) {
        return this->tokens_[this->at_ - 1];
    }

    return Token(T_EOF, "", "", 0);
}

Token Parser::Consume(TokenType type, std::string message)
{
    if (Check(type)) {
        return Advance();
    }

    throw Error(Peek(), message);
}

ParseError Parser::Error(Token token, std::string message)
{
    Error::MakeError(token, message);
    return ParseError();
}

// If parser encounters an error, Synchronize will skip tokens until it gets to the next statement
void Parser::Synchronize()
{
    Advance();

    while (!End()) {
        if (Previous().type() == SEMICOLON) {
            return;
        }

        switch (Peek().type()) {
        case FUNCTION:
        case WHILE:
        case REPEAT:
        case IF:
        case FOR:
        case BREAK:
        case LOCAL:
        case DO:
            return;
        default:
            Advance();
            break;
        }
    }
}
