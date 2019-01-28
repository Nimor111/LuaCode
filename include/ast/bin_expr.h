#ifndef BIN_EXPR_H
#define BIN_EXPR_H

#include "expr.h"

class BinExpr : public Expr {
private:
    Expr* left_;
    Token op_;
    Expr* right_;

public:
    BinExpr(Expr*, Token, Expr*);
    void Accept(Visitor* visitor) override;
    Expr* left() const;
    Expr* right() const;
    Token op() const;
};

#endif /* BIN_EXPR_H */
