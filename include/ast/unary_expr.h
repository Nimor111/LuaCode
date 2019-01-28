#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H

#include "expr.h"

class UnaryExpr : public Expr {
private:
    Expr* right_;
    Token op_;

public:
    UnaryExpr(Token, Expr*);
    void Accept(Visitor* visitor) override;
    Expr* right() const;
    Token op() const;
};

#endif /* UNARY_EXPR_H */
